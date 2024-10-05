#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <QApplication>


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

int get_cost_of_one(Language language) {
    switch(language) {
        case Language::English:
            return 800;
        case Language::French:
            return 500;
        case Language::German:
            return 500;
        case Language::Japanese:
            return 400;
        case Language::Chinese:
            return 700;
        case Language::Spanish:
            return 700;
    }
}

class Group {
public:
    Group(Language language, Level level, int cost): language_(language), level_(level), cost_(cost) {}
    Language get_language () {
        return language_;
    }
    Level get_level () {
        return level_;
    }
    int get_cost () {
        return cost_;
    }
    void set_language (Language language) {
        language_ = language;
    }
    void set_level (Level level) {
        level_ = level;
    }
    void set_cost (int cost) {
        cost_ = cost;
    }
private:
    Language language_;
    Level level_;
    int cost_;
};

class Consumer {
public:
    Consumer(std::string surname): surname_(surname) {
        
    }
    std::string get_surname () {
        return surname_;
    }
    void pay (int amount) {
        paidAmount += amount;
    }
    void visit() {
        ++visits_;
    }
    bool checkAmount (int amount) {
        if (paidAmount >= amount) {
            paidAmount -= amount;
            return 1;
        } else return 0;
    }
    bool checkVisits () {
        if (visits_ == 0) return 0;
        visits_ = 0;
        return 1;
    }
private:
    std::string surname_;
    int paidAmount = 0, visits_ = 0;
};

class NonIndividual : public Group {
public:
    NonIndividual(Language language, Level level, int cost, int length, int lessonsPerWeek, Intensity intencity) : Group(language, level, cost), length_(length), lessonsPerWeek_(lessonsPerWeek), intencity_(intencity) {}
    ~NonIndividual() {
        while (first != nullptr) delFirst();
    }
    void add(Consumer * consumer) {
        amountOfPeople_++;
        if (first == nullptr) {
            first = new node(consumer);
            last = first;
            return;
        } else {
            last->next = new node(consumer);
            last = last->next;
        }
    }
    void remove(Consumer * consumer) {
        if (first == nullptr) return;
        amountOfPeople_--;
        if (first->consumer_ == consumer) {
            delFirst();
            return;
        }
        node * cur = first;
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
    std::vector <Consumer *> get_consumers () {
        std::vector <Consumer *> answer;
        node * cur = first;
        while (cur != nullptr) {
            answer.push_back(cur->consumer_);
            cur = cur->next;
        }
        return answer;
    }
    void print () {
        //for testing only
        node * cur = first;
        while (cur != nullptr) {
            std::cout << cur->consumer_->get_surname() << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }
    bool recount() {
        while (first != nullptr && !check(first)) {
            delFirst();
        }
        node * cur = first;
        while (cur != nullptr) {
            if (cur->next != nullptr) {
                if (checkNext(cur)) cur = cur->next;
            } else {
                cur = cur->next;
            }
        }
        if (curLength_ >= length_) {
            curLength_ = 0;
            switch(get_level()) {
                case Level::Beg:
                    set_level(Level::Mid);
                    break;
                case Level::Mid:
                    set_level(Level::Pro);
                    break;
                case Level::Pro:
                    return 0;
            }
        }
        return 1;
    }
    void day () {
        ++curLength_;
    }
    void addDays(int days) {
        curLength_ += days;
    }
    Intensity get_intencity () {
        return intencity_;
    }
    int get_amount () {
        return amountOfPeople_;
    }
protected:
    void check (Consumer * consumer) {
        if (!consumer->checkAmount(get_cost()) || !consumer->checkVisits()) {
            remove(consumer);
        }
    }
private:
    int amountOfPeople_ = 0;
    int length_ = 0;
    int curLength_ = 0;
    int lessonsPerWeek_ = 0;
    Intensity intencity_;
    struct node {
        Consumer * consumer_;
        node * next = nullptr;
        node (Consumer * consumer): consumer_(consumer) {}
    };
    void del_next (node * t) {
        amountOfPeople_--;
        node * n = t->next;
        t->next = n->next;
        if (last == n) last = t;
        delete n;
    }
    node * first = nullptr, * last = nullptr;
    bool checkNext (node * t) {
        node * n = t->next;
        if (!n->consumer_->checkAmount(get_cost()) || !n->consumer_->checkVisits()) {
            del_next(t);
            return 0;
        }
        return 1;
    }
    bool check(node * t) {
        if (t == nullptr) return 0;
        if (!t->consumer_->checkAmount(get_cost()) || !t->consumer_->checkVisits()) {
            return 0;
        }
        return 1;
    }
    void delFirst () {
        amountOfPeople_--;
        node * n = first->next;
        delete first;
        first = n;
        if (first == nullptr) last = nullptr;
    }
};
class usualGroupCouse : public NonIndividual {
public:
    usualGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 2, 100, 2, Intensity::usual) {}
};
class supportiveGroupCouse : public NonIndividual {
public:
    supportiveGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 1, 200, 1, Intensity::supportive) {}
};
class intensiveGroupCouse : public NonIndividual {
public:
    intensiveGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 5, 20, 5, Intensity::intensive) {}
};
class Individual : public Group {
public:
    Individual(Language language, Level level, Intensity intencity, Consumer * consumer): Group(language, level, get_cost_of_one(language)), consumer_(consumer), intencity_(intencity) {}
    Consumer * get_consumer () {
        return consumer_;
    }
    Intensity get_intencity () {
        return intencity_;
    }
private:
    Consumer * consumer_;
    Intensity intencity_;
};
class Course {
public:
    Course () {}
    ~Course () {
        for (auto u : groups_) {
            delete u;
        }
        for (auto u : individuals_) {
            delete u;
        }
    }
    void addPeople (std::vector <Consumer *> consumers, std::vector <Language> languages, std::vector <Level> levels, std::vector <Intensity> intencities) {
        int groupSize = 10;
        std::map<std::pair<std::pair<Language, Level>, Intensity>, std::vector<Consumer *>> users;
        std::map<std::pair<std::pair<Language, Level>, Intensity>, std::vector<NonIndividual *>> group;
        for (int i = 0; i < consumers.size(); ++ i) {
           users[std::make_pair(std::make_pair(languages[i], levels[i]), intencities[i])].push_back(consumers[i]);
       }
        for (auto u: individuals_) {
            users[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intencity())].push_back(u->get_consumer());
            delete u;
        }
        individuals_.clear();
       for (auto u: groups_) {
           group[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intencity())].push_back(u);
       }
        for (auto it : users) {
            std::pair<std::pair<Language, Level>, Intensity> f = it.first;
            std::vector<Consumer *> s = it.second;
            std::vector<NonIndividual *> p = group[f];
            for (NonIndividual * Group : p) {
                while (Group->get_amount() < groupSize && s.size() > 0) {
                    Group->add(s[s.size() - 1]);
                    s.pop_back();
                }
                if (Group->get_amount() < 5) {
                    for (auto u: Group->get_consumers()) {
                        s.push_back(u);
                        deleteGroup(Group);
                        delete Group;
                        Group = nullptr;
                    }
                }
            }
            int fsize = s.size();
            for (int i = 0; i < fsize / groupSize; ++i) {
                switch(f.second) {
                    case Intensity::usual:
                        addGroup(new usualGroupCouse(f.first.first, f.first.second));
                        break;
                    case Intensity::supportive:
                        addGroup(new supportiveGroupCouse(f.first.first, f.first.second));
                        break;
                    case Intensity::intensive:
                        addGroup(new intensiveGroupCouse(f.first.first, f.first.second));
                        break;
                }
                int ssize = s.size();
                for (int j = ssize - 1; j >= ssize - groupSize; j--) {
                    groups_[amountOfGroups - 1]->add(s[j]);
                    s.pop_back();
                }
            }
            while(s.size() > 0) {
                individuals_.push_back(new Individual(f.first.first, f.first.second, f.second, s[s.size() - 1]));
                s.pop_back();
            }
            
            
            
        }
    }
    void recount () {
        std::vector <NonIndividual *> toRemove;
        for (auto u: groups_) {
            u->recount();
            if (u->get_amount() == 0) {
                toRemove.push_back(u);
            }
        }
        for (auto u: toRemove) {
            deleteGroup(u);
            delete u;
        }
    }
    std::vector <NonIndividual *> get_non_individual () {
        std::vector <NonIndividual *> answer = groups_;
        return answer;
    }
    void print() {
        for (auto u: groups_) {
            u->print();
        }
    }
private:
    std::vector <NonIndividual *> groups_;
    std::vector <Individual *> individuals_;
    int amountOfGroups = 0;
    void addGroup (NonIndividual * group) {
        groups_.push_back(group);
        ++amountOfGroups;
    }
    void deleteGroup (NonIndividual * group) {
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
int main() {
    Consumer * a = new Consumer("a");
    Consumer * b = new Consumer("b");
    Consumer * c = new Consumer("c");
    Consumer * d = new Consumer("d");
    Consumer * e = new Consumer("e");
    Consumer * f = new Consumer("f");
    std::vector <Consumer *> consumers;
    std::vector <Language> languages;
    std::vector <Level> levels;
    std::vector <Intensity> intencities;
    consumers.push_back(a);
    consumers.push_back(b);
    consumers.push_back(c);
    //consumers.push_back(d);
    consumers.push_back(e);
    consumers.push_back(f);
    languages.push_back(Language::English);
    languages.push_back(Language::English);
    languages.push_back(Language::English);
    //languages.push_back(Language::English);
    languages.push_back(Language::Spanish);
    languages.push_back(Language::Spanish);
    levels.push_back(Level::Beg);
    levels.push_back(Level::Beg);
    levels.push_back(Level::Beg);
    //levels.push_back(Level::Begin);
    levels.push_back(Level::Beg);
    levels.push_back(Level::Beg);
    intencities.push_back(Intensity::usual);
    intencities.push_back(Intensity::usual);
    intencities.push_back(Intensity::usual);
    //intencities.push_back(Intencity::usual);
    intencities.push_back(Intensity::usual);
    intencities.push_back(Intensity::usual);
    Course course;
    course.addPeople(consumers, languages, levels, intencities);
    course.print();
    consumers.clear();
    languages.clear();
    levels.clear();
    intencities.clear();
    //consumers.push_back(c);
    //consumers.push_back(d);
    //languages.push_back(Language::English);
    //languages.push_back(Language::English);
    //levels.push_back(Level::Begin);
    //levels.push_back(Level::Begin);
    //intencities.push_back(Intencity::usual);
    //intencities.push_back(Intencity::usual);
    a->pay(1000000);
    a->visit();
    b->pay(100000);
    b->visit();
    course.recount();
    course.print();
    course.addPeople(consumers, languages, levels, intencities);
    course.print();
    return 0;
}
