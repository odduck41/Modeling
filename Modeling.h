#pragma once
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace Md {

enum class Language {
  English,
  French,
  German,
  Japanese,
  Chinese,
  Spanish
};

enum class Level {
  Beg,
  Mid,
  Pro
};

enum class Intensity {
  usual,
  supportive,
  intensive
};

inline long long get_cost(const Language& language) {
    switch (language) {
        case Language::English:
            return 800;
        case Language::French:
        case Language::German:
            return 500;
        case Language::Japanese:
            return 400;
        case Language::Chinese:
        case Language::Spanish:
            return 700;
        default:
            return 0;
    }
}

class Group {
  public:
    Group(Language language, Level level, int cost)
            : language_(language), level_(level), cost_(cost) { }

    Language get_language() {
        return language_;
    }

    Level get_level() {
        return level_;
    }

    [[nodiscard]] long long get_cost() const {
        return cost_;
    }

    void set_language(Language language) {
        language_ = language;
    }

    void set_level(Level level) {
        level_ = level;
    }

    void set_cost(int cost) {
        cost_ = cost;
    }

  private:
    Language language_;
    Level level_;
    long long cost_;
};

class Consumer {
  public:
    explicit Consumer(std::string surname)
            : surname_(std::move(surname)) { }

    std::string get_surname() {
        return surname_;
    }

    void pay(int amount) {
        paidAmount += amount;
    }

    void visit() {
        ++visits_;
    }

    bool checkAmount(long long amount) {
        if (paidAmount >= amount) {
            paidAmount -= amount;
            return true;
        }
        return false;
    }

    bool checkVisits() {
        if (visits_ == 0) return false;
        visits_ = 0;
        return true;
    }

  private:
    std::string surname_;
    long long paidAmount = 0, visits_ = 0;
};

class NonIndividual : public Group {
  public:
    NonIndividual(Language language, Level level, int cost, int length, int lessonsPerWeek, Intensity intensity)
            : Group(language, level, cost), length_(length), lessonsPerWeek_(lessonsPerWeek), intensity_(intensity) { }

    ~NonIndividual() {
        while (first != nullptr) delFirst();
    }

    void add(Consumer* consumer) {
        amountOfPeople_++;
        if (first == nullptr) {
            first = new node(consumer);
            last = first;
            return;
        }
        else {
            last->next = new node(consumer);
            last = last->next;
        }
    }

    void remove(Consumer* consumer) {
        if (first == nullptr) return;
        amountOfPeople_--;
        if (first->consumer_ == consumer) {
            delFirst();
            return;
        }
        node* cur = first;
        while (cur != nullptr) {
            if (cur->next != nullptr) {
                if (cur->next->consumer_ == consumer) {
                    del_next(cur);
                    return;
                }
            }
            cur = cur->next;
        }
    }

    std::vector<Consumer*> get_consumers() {
        std::vector<Consumer*> answer;
        node* cur = first;
        while (cur != nullptr) {
            answer.push_back(cur->consumer_);
            cur = cur->next;
        }
        return answer;
    }

    bool recount() {
        while (first != nullptr && !check(first)) {
            delFirst();
        }
        node* cur = first;
        while (cur != nullptr) {
            if (cur->next != nullptr) {
                if (checkNext(cur)) cur = cur->next;
            }
            else {
                cur = cur->next;
            }
        }
        if (curLength_ >= length_) {
            curLength_ = 0;
            switch (get_level()) {
                case Level::Beg:
                    set_level(Level::Mid);
                    break;
                case Level::Mid:
                    set_level(Level::Pro);
                    break;
                case Level::Pro:
                    return false;
            }
        }
        return true;
    }

    void day() {
        ++curLength_;
    }

    void addDays(int days) {
        curLength_ += days;
    }

    [[maybe_unused]] Intensity get_intensity() {
        return intensity_;
    }

    [[nodiscard]] long long get_amount() const {
        return amountOfPeople_;
    }

  protected:
    void check(Consumer* consumer) {
        if (!consumer->checkAmount(get_cost()) || !consumer->checkVisits()) {
            remove(consumer);
        }
    }

  private:
    long long amountOfPeople_ = 0;
    long long length_ = 0;
    long long curLength_ = 0;
    long long lessonsPerWeek_ = 0;
    Intensity intensity_;

    struct node {
      Consumer* consumer_;
      node* next = nullptr;

      explicit node(Consumer* consumer)
              : consumer_(consumer) { }
    };

    void del_next(node* t) {
        amountOfPeople_--;
        node* n = t->next;
        t->next = n->next;
        if (last == n) last = t;
        delete n;
    }

    node* first = nullptr, * last = nullptr;

    bool checkNext(node* t) {
        node* n = t->next;
        if (!n->consumer_->checkAmount(get_cost()) || !n->consumer_->checkVisits()) {
            del_next(t);
            return false;
        }
        return true;
    }

    bool check(node* t) {
        if (t == nullptr) return false;
        if (!t->consumer_->checkAmount(get_cost()) || !t->consumer_->checkVisits()) {
            return false;
        }
        return true;
    }

    void delFirst() {
        amountOfPeople_--;
        node* n = first->next;
        delete first;
        first = n;
        if (first == nullptr) last = nullptr;
    }
};

class usualGroupCourse : public NonIndividual {
  public:
    usualGroupCourse(Language language, Level level)
            : NonIndividual(language, level, Md::get_cost(language) * 2 * 2, 100, 2, Intensity::usual) { }
};

class supportiveGroupCourse : public NonIndividual {
  public:
    supportiveGroupCourse(Language language, Level level)
            : NonIndividual(language, level, Md::get_cost(language) * 2 * 1, 200, 1, Intensity::supportive) { }
};

class intensiveGroupCourse : public NonIndividual {
  public:
    intensiveGroupCourse(Language language, Level level)
            : NonIndividual(language, level, Md::get_cost(language) * 2 * 5, 20, 5, Intensity::intensive) { }
};

class Individual : public Group {
  public:
    Individual(Language language, Level level, Intensity intensity, Consumer* consumer)
            : Group(language, level, Md::get_cost(language)), consumer_(consumer), intensity_(intensity) { }

    Consumer* get_consumer() {
        return consumer_;
    }

    Intensity get_intensity() {
        return intensity_;
    }

  private:
    Consumer* consumer_;
    Intensity intensity_;
};

class Course {
  public:
    Course() = default;

    ~Course() {
        for (auto u : groups_) {
            delete u;
        }
        for (auto u : individuals_) {
            delete u;
        }
    }

    void addPeople(const std::vector<Consumer*>& consumers, const std::vector<Language>& languages,
            const std::vector<Level>& levels, const std::vector<Intensity>& intensities) {
        int groupSize = 10;
        std::map<std::pair<std::pair<Language, Level>, Intensity>, std::vector<Consumer*>> users;
        std::map<std::pair<std::pair<Language, Level>, Intensity>, std::vector<NonIndividual*>> group;
        for (int i = 0; i < consumers.size(); ++i) {
            users[std::make_pair(std::make_pair(languages[i], levels[i]), intensities[i])].push_back(consumers[i]);
        }
        for (auto u : individuals_) {
            users[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intensity())].push_back(
                    u->get_consumer());
            delete u;
        }
        individuals_.clear();
        for (auto u : groups_) {
            group[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intensity())].push_back(u);
        }
        for (auto it : users) {
            std::pair<std::pair<Language, Level>, Intensity> f = it.first;
            std::vector<Consumer*> s = it.second;
            std::vector<NonIndividual*> p = group[f];
            for (NonIndividual* Group : p) {
                while (Group->get_amount() < groupSize && s.size() > 0) {
                    Group->add(s[s.size() - 1]);
                    s.pop_back();
                }
                if (Group->get_amount() < 5) {
                    for (auto u : Group->get_consumers()) {
                        s.push_back(u);
                        deleteGroup(Group);
                        delete Group;
                        Group = nullptr;
                    }
                }
            }
            auto f_size = s.size();
            for (auto i = 0ull; i < f_size / groupSize; ++i) {
                switch (f.second) {
                    case Intensity::usual:
                        addGroup(new usualGroupCourse(f.first.first, f.first.second));
                        break;
                    case Intensity::supportive:
                        addGroup(new supportiveGroupCourse(f.first.first, f.first.second));
                        break;
                    case Intensity::intensive:
                        addGroup(new intensiveGroupCourse(f.first.first, f.first.second));
                        break;
                }
                auto s_size = s.size();
                for (auto j = s_size - 1; j >= s_size - groupSize; j--) {
                    groups_[amountOfGroups - 1]->add(s[j]);
                    s.pop_back();
                }
            }
            while (!s.empty()) {
                individuals_.push_back(new Individual(f.first.first, f.first.second, f.second, s[s.size() - 1]));
                s.pop_back();
            }

        }
    }

    void recount() {
        std::vector<NonIndividual*> toRemove;
        for (auto u : groups_) {
            u->recount();
            if (u->get_amount() == 0) {
                toRemove.push_back(u);
            }
        }
        for (auto u : toRemove) {
            deleteGroup(u);
            delete u;
        }
    }

    std::vector<NonIndividual*> get_non_individual() {
        std::vector<NonIndividual*> answer = groups_;
        return answer;
    }

  private:
    std::vector<NonIndividual*> groups_;
    std::vector<Individual*> individuals_;
    int amountOfGroups = 0;

    void addGroup(NonIndividual* group) {
        groups_.push_back(group);
        ++amountOfGroups;
    }

    void deleteGroup(NonIndividual* group) {
        for (int i = 0; i < amountOfGroups; ++i) {
            if (groups_[i] == group) {
                for (int j = i + 1; j < amountOfGroups; ++j) {
                    groups_[j - 1] = groups_[j];
                }
                groups_.pop_back();
                --amountOfGroups;
                break;
            }
        }
    }
};
}
