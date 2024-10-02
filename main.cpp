#include <iostream>
#include <vector>
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
    Consumer(std::string name, std::string surname): name_(name), surname_(surname) {}
    std::string get_name () {
        return name_;
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
    std::string name_, surname_;
    int paidAmount = 0, visits_ = 0;
};

class NonIndividual : public Group {
public:
    NonIndividual(Language language, Level level, int cost, int length) : Group(language, level, cost), length_(length) {}
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
            std::cout << cur->consumer_->get_name() << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }
    //virtual void setLength (int x) = 0;
    void recount() {
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
        //check length, update level
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
    struct node {
        Consumer * consumer_;
        node * next = nullptr;
        node (Consumer * consumer): consumer_(consumer) {}
    };
    void del_next (node * t) {
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
        node * n = first->next;
        delete first;
        first = n;
        if (first == nullptr) last = nullptr;
    }
};


int main() {
    NonIndividual course(Language::English, Level::Mid, 1, 1);
    Consumer * a = new Consumer("a", "a");
    Consumer * b = new Consumer("b", "b");
    Consumer * c = new Consumer("c", "c");
    course.add(a);
    course.add(b);
    course.add(c);
    course.print();
    //a->pay(1);
    //b->pay(1);
    c->pay(2);
    //a->visit();
    //b->visit();
    c->visit();
    course.recount();
    course.print();
    
    return 0;
}
