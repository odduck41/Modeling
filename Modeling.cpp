#include "Modeling.h"

#include <fstream>

static std::random_device dev;
static std::mt19937 generator(dev());


Lesson::Lesson(const Data& data)
        : data_(data) { }

Language Lesson::getLanguage() const {
    return data_.language_;
}

Intensity Lesson::getIntensity() const {
    return data_.intensity_;
}

Level Lesson::getLevel() const {
    return data_.level_;
}

long long Lesson::getCost() const {
    long long cost = 0;

    cost += this->data_.language_ * 300;
    cost += this->data_.level_ * 200;
    cost += this->data_.intensity_ * 100;

    if (
        auto _ = dynamic_cast<const Individual*>(this);
            _ != nullptr
            ) {
        cost += 2000;
    } else {
        cost += 1000;
    }

    return cost;
}


Consumer::Consumer(const std::vector<Data>& data)
          : data_(data)  {
    parse();
    name_ = names_[generator() % names_.size()];
    surname_ = surnames_[generator() % surnames_.size()];

}

void Consumer::parse() {
    static bool called = false;
    if (called) return;

    std::ifstream is("names.txt");
    std::string line;
    while (std::getline(is, line)) {
        std::string name;
        for (auto& i : line) {
            if (i != ' ') {
                name += i;
            } else {
                names_.push_back(name);
            }
        }
        names_.push_back(name);
    }

    is.close();

    is.open("surnames.txt");

    while (std::getline(is, line)) {
        std::string surname;
        for (auto& i : line) {
            if (i != ' ') {
                surname += i;
            } else {
                surnames_.push_back(surname);
            }
        }
        surnames_.push_back(surname);
    }

    called = true;
}

bool Consumer::rejected(const bool& approved) {
    if (approved) {
        return true;
    }
    return generator() % 2;
}

bool Consumer::pay(const long long& price) {
    return (generator() / price + generator() % price) % 101 <= 85;
}

void Consumer::update(const Language& lang) {
    if (courses_.contains(lang)) {
        courses_.erase(lang);
        return;
    }
    courses_.insert(lang);
}

bool Consumer::alive() const {
    return courses_.empty();
}

std::string Consumer::getSurname() const {
    return surname_;
}

std::string Consumer::getName() const {
    return name_;
}


Data::Data(const Language& language)
    : language_(language),
      intensity_(Intensity(generator() % 3 + 1)),
      level_(Level(generator() % 3 + 1)){
}

Application::Application(const std::vector<Language>& allowed) {
    size_t amount = 0;

    if (generator() % 101 <= 89) {
        amount = 1;
    } else {
        amount = (generator() % 101 % 3 + 1) % allowed.size();
    }

    for (auto i = 0; i < amount; ++i) {
        data.emplace_back(allowed[i]);
    }
}

Individual::Individual(const Data& data, Consumer* consumer)
            : Lesson(data), consumer_(consumer) {}

Consumer* Individual::who() const {
    return consumer_;
}

void Individual::update() {
    if (!Consumer::pay(getCost())) {
        consumer_->update(data_.language_);
        consumer_ = nullptr;
    }
}


Group::Group(const Data& data)
    : Lesson(data) {

}

void Group::add(Consumer* consumer) {
    consumers_.push_back(consumer);
}

void Group::update() {
    for (auto i = consumers_.begin(); i != consumers_.end(); ++i) {
        if (!Consumer::pay(getCost())) {
            (*i)->update(data_.language_);
            consumers_.erase(i);
            --i;
        }
    }
}

bool Group::full() const {
    return consumers_.size() == 10;
}

Course::Course(const Language& language) : language_(language) {
    for (long long level = 1; level <= 3; ++level) {
        for (long long intensity = 1; intensity <= 3; ++intensity) {
            Data data{Language(language), Level(level), Intensity(intensity)};
            groups_[data] = new Group(data);
        }
    }
}

void Course::add(Application* app) {

}

void Course::reorder() {

}
