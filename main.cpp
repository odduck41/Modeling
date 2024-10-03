#include <iostream>
#include <vector>
#include <map>
enum class Language {
    English,
    French,
    German,
    Japanese,
    Chinese,
    Spanish
};
enum class Level {
    Begin,
    Mid,
    Pro
};
enum class Intencity {
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
    NonIndividual(Language language, Level level, int cost, int length, int lessonsPerWeek, Intencity intencity) : Group(language, level, cost), length_(length), lessonsPerWeek_(lessonsPerWeek), intencity_(intencity) {}
    ~NonIndividual() {
        while (first != nullptr) delFirst();
    }
    void add(Consumer * consumer) {
        if (first == nullptr) {
            first = new node(consumer);
            last = first;
            return;
        } else {
            last->next = new node(consumer);
            last = last->next;
        }
        amountOfPeople_++;
    }
    void remove(Consumer * consumer) {
        if (first == nullptr) return;
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
        amountOfPeople_--;
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
                case Level::Begin:
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
    Intencity get_intencity () {
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
    Intencity intencity_;
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
    usualGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 2, 100, 2, Intencity::usual) {}
};
class supportiveGroupCouse : public NonIndividual {
public:
    supportiveGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 1, 200, 1, Intencity::supportive) {}
};
class intensiveGroupCouse : public NonIndividual {
public:
    intensiveGroupCouse(Language language, Level level) : NonIndividual(language, level, get_cost_of_one(language) * 2 * 5, 20, 5, Intencity::intensive) {}
};
class Course {
public:
    Course () {}
    void addPeople (std::vector <Consumer *> consumers, std::vector <Language> languages, std::vector <Level> levels, std::vector <Intencity> intencities) {
        int groupSize = 2;
        std::map<std::pair<std::pair<Language, Level>, Intencity>, std::vector<Consumer *>> users;
        std::map<std::pair<std::pair<Language, Level>, Intencity>, std::vector<NonIndividual *>> group;
        for (int i = 0; i < consumers.size(); ++ i) {
           users[std::make_pair(std::make_pair(languages[i], levels[i]), intencities[i])].push_back(consumers[i]);
       }
       for (auto u: groups_) {
           group[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intencity())].push_back(u);
       }
        for (auto it : users) {
            std::pair<std::pair<Language, Level>, Intencity> f = it.first;
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
                    case Intencity::usual:
                        addGroup(new usualGroupCouse(f.first.first, f.first.second));
                    case Intencity::supportive:
                        addGroup(new supportiveGroupCouse(f.first.first, f.first.second));
                    case Intencity::intensive:
                        addGroup(new intensiveGroupCouse(f.first.first, f.first.second));
                }
                int ssize = s.size();
                for (int j = ssize - 1; j >= ssize - groupSize; j--) {
                    groups_[amountOfGroups - 1]->add(s[j]);
                    s.pop_back();
                }
            }
            
            
        }
    }
    void print() {
        for (auto u: groups_) {
            u->print();
        }
    }
private:
    std::vector <NonIndividual *> groups_;
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
    std::vector <Intencity> intencities;
    consumers.push_back(a);
    consumers.push_back(b);
    //consumers.push_back(c);
    //consumers.push_back(d);
    consumers.push_back(e);
    consumers.push_back(f);
    languages.push_back(Language::English);
    languages.push_back(Language::English);
    //languages.push_back(Language::English);
    //languages.push_back(Language::English);
    languages.push_back(Language::Spanish);
    languages.push_back(Language::Spanish);
    levels.push_back(Level::Begin);
    levels.push_back(Level::Begin);
    //levels.push_back(Level::Begin);
    //levels.push_back(Level::Begin);
    levels.push_back(Level::Begin);
    levels.push_back(Level::Begin);
    intencities.push_back(Intencity::usual);
    intencities.push_back(Intencity::usual);
    //intencities.push_back(Intencity::usual);
    //intencities.push_back(Intencity::usual);
    intencities.push_back(Intencity::usual);
    intencities.push_back(Intencity::usual);
    Course course;
    course.addPeople(consumers, languages, levels, intencities);
    course.print();
    consumers.clear();
    languages.clear();
    levels.clear();
    intencities.clear();
    consumers.push_back(c);
    consumers.push_back(d);
    languages.push_back(Language::English);
    languages.push_back(Language::English);
    levels.push_back(Level::Begin);
    levels.push_back(Level::Begin);
    intencities.push_back(Intencity::usual);
    intencities.push_back(Intencity::usual);
    course.addPeople(consumers, languages, levels, intencities);
    course.print();
    return 0;
}



/*
 Some crazy algorithm
 
 
 for (int i = 0; i < consumers.size(); ++ i) {
    users[std::make_pair(std::make_pair(languages[i], levels[i]), intencities[i])].push_back(consumers[i]);
}
for (auto u: groups_) {
    group[std::make_pair(std::make_pair(u->get_language(), u->get_level()), u->get_intencity())].push_back(u);
}
for (auto it : users) {
    std::pair<std::pair<Language, Level>, Intencity> f = it.first;
    std::vector<Consumer *> s = it.second;
    std::vector<NonIndividual *> p = group[f];
    for (int i = 5; i <= 7; ++i) {
        if (s.size() == 0) break;
        for (auto u: p) {
            if (s.size() == 0) break;
            while (u->get_amount() < i && s.size() > 0) {
                u->add(s[s.size() - 1]);
                s.pop_back();
            }
        }
    }
    if (s.size() == 0) {
        for (auto u: p) {
            if (u->get_amount() < 5) {
                for (auto it : u->get_consumers()) {
                    s.push_back(it);
                }
                deleteGroup(u);
                delete u;
            }
        }
    }
    for (int i = 0; i <= s.size() / 7; ++i) {
        switch(f.second) {
            case Intencity::usual:
                addGroup(new usualGroupCouse(f.first.first, f.first.second));
            case Intencity::supportive:
                addGroup(new supportiveGroupCouse(f.first.first, f.first.second));
            case Intencity::intensive:
                addGroup(new intensiveGroupCouse(f.first.first, f.first.second));
        }
        int ssize = s.size();
        for (int j = s.size() - 1; j >= s.size() - 7; j--) {
            groups_[amountOfGroups - 1]->add(s[j]);
            s.pop_back();
        }
    }
    
}*/
