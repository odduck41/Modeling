#include "Modeling.h"

long long Md::get_cost(const Md::Language& language) {
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

Md::Language Md::Group::get_language() {
    return language_;
}

Md::Level Md::Group::get_level() {
    return level_;
}

long long Md::Group::get_cost() const {
    return cost_;
}

void Md::Group::set_language(Md::Language language) {
    language_ = language;
}

void Md::Group::set_level(Md::Level level) {
    level_ = level;
}

void Md::Group::set_cost(int cost) {
    cost_ = cost;
}

Md::Group::Group(Md::Language language, Md::Level level, long long int cost)
        : language_(language), level_(level), cost_(cost) { }

std::string Md::Consumer::get_surname() {
    return surname_;
}

void Md::Consumer::pay(int amount) {
    paidAmount += amount;
}

void Md::Consumer::visit() {
    ++visits_;
}

bool Md::Consumer::checkAmount(long long int amount) {
    if (paidAmount >= amount) {
        paidAmount -= amount;
        return true;
    }
    return false;
}

bool Md::Consumer::checkVisits() {
    if (visits_ == 0) return false;
    visits_ = 0;
    return true;
}

Md::Consumer::Consumer(std::string surname)
        : surname_(std::move(surname)) { }

Md::NonIndividual::~NonIndividual() {
    while (first != nullptr) delFirst();
}

void Md::NonIndividual::add(Md::Consumer* consumer) {
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

void Md::NonIndividual::remove(Md::Consumer* consumer) {
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

std::vector<Md::Consumer*> Md::NonIndividual::get_consumers() {
    std::vector<Md::Consumer*> answer;
    node* cur = first;
    while (cur != nullptr) {
        answer.push_back(cur->consumer_);
        cur = cur->next;
    }
    return answer;
}

bool Md::NonIndividual::recount() {
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

void Md::NonIndividual::day() {
    ++curLength_;
}

void Md::NonIndividual::addDays(int days) {
    curLength_ += days;
}

Md::Intensity Md::NonIndividual::get_intensity() {
    return intensity_;
}

long long Md::NonIndividual::get_amount() const {
    return amountOfPeople_;
}

void Md::NonIndividual::check(Md::Consumer* consumer) {
    if (!consumer->checkAmount(get_cost()) || !consumer->checkVisits()) {
        remove(consumer);
    }
}

void Md::NonIndividual::del_next(Md::NonIndividual::node* t) {
    amountOfPeople_--;
    node* n = t->next;
    t->next = n->next;
    if (last == n) last = t;
    delete n;
}

bool Md::NonIndividual::checkNext(Md::NonIndividual::node* t) {
    node* n = t->next;
    if (!n->consumer_->checkAmount(get_cost()) || !n->consumer_->checkVisits()) {
        del_next(t);
        return false;
    }
    return true;
}

bool Md::NonIndividual::check(Md::NonIndividual::node* t) {
    if (t == nullptr) return false;
    if (!t->consumer_->checkAmount(get_cost()) || !t->consumer_->checkVisits()) {
        return false;
    }
    return true;
}

void Md::NonIndividual::delFirst() {
    amountOfPeople_--;
    node* n = first->next;
    delete first;
    first = n;
    if (first == nullptr) last = nullptr;
}

Md::NonIndividual::NonIndividual(Md::Language language, Md::Level level, long long int cost, int length,
        int lessonsPerWeek, Md::Intensity intensity)
        : Group(language, level, cost), length_(length), lessonsPerWeek_(lessonsPerWeek), intensity_(intensity) { }

Md::Consumer* Md::Individual::get_consumer() {
    return consumer_;
}

Md::Intensity Md::Individual::get_intensity() {
    return intensity_;
}

Md::Individual::Individual(Md::Language language, Md::Level level, Md::Intensity intensity, Md::Consumer* consumer)
        : Group(language, level, Md::get_cost(language)), consumer_(consumer), intensity_(intensity) { }

Md::Course::~Course() {
    for (auto u : groups_) {
        delete u;
    }
    for (auto u : individuals_) {
        delete u;
    }
}

void Md::Course::addPeople(const std::vector<Consumer*>& consumers, const std::vector<Language>& languages,
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
    for (const auto& it : users) {
        std::pair<std::pair<Language, Level>, Intensity> f = it.first;
        std::vector<Consumer*> s = it.second;
        std::vector<NonIndividual*> p = group[f];
        for (NonIndividual* Group : p) {
            while (Group->get_amount() < groupSize && !s.empty()) {
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

void Md::Course::recount() {
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

std::vector<Md::NonIndividual*> Md::Course::get_non_individual() {
    std::vector<Md::NonIndividual*> answer = groups_;
    return answer;
}

void Md::Course::addGroup(Md::NonIndividual* group) {
    groups_.push_back(group);
    ++amountOfGroups;
}

void Md::Course::deleteGroup(Md::NonIndividual* group) {
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

Md::intensiveGroupCourse::intensiveGroupCourse(Md::Language language, Md::Level level)
        : NonIndividual(language, level, Md::get_cost(language) * 2 * 5, 20, 5, Intensity::intensive) { }

Md::supportiveGroupCourse::supportiveGroupCourse(Md::Language language, Md::Level level)
        : NonIndividual(language, level, Md::get_cost(language) * 2 * 1, 200, 1, Intensity::supportive) { }

Md::usualGroupCourse::usualGroupCourse(Md::Language language, Md::Level level)
        : NonIndividual(language, level, Md::get_cost(language) * 2 * 2, 100, 2, Intensity::usual) { }

Md::NonIndividual::node::node(Md::Consumer* consumer)
        : consumer_(consumer) { }
