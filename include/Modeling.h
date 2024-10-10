#pragma once
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <thread>

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

inline long long get_cost(const Language& language);

class Group {
  public:
    Group(Language, Level, long long);

    Language get_language();
    Level get_level();
    [[nodiscard]] long long get_cost() const;
    void set_language(Language);
    void set_level(Level);
    void set_cost(int);
  private:
    Language language_;
    Level level_;
    long long cost_;
};

class Consumer {
  public:
    explicit Consumer(std::string);

    std::string get_surname();
    void pay(int);
    void visit();
    bool checkAmount(long long);
    bool checkVisits();
  private:
    std::string surname_;
    long long paidAmount = 0, visits_ = 0;
};

class NonIndividual : public Group {
  public:
    NonIndividual(Language, Level, long long, int, int, Intensity);

    void add(Consumer*);
    void remove(Consumer*);
    std::vector<Consumer*> get_consumers();
    bool recount();
    void day();
    void addDays(int);
    [[maybe_unused]] Intensity get_intensity();
    [[nodiscard]] long long get_amount() const;

    ~NonIndividual();
  protected:
    void check(Consumer*);
  private:
    struct node {
      explicit node(Consumer*);
      Consumer* consumer_;
      node* next = nullptr;
    };

    long long amountOfPeople_ = 0;
    long long length_ = 0;
    long long curLength_ = 0;
    long long lessonsPerWeek_ = 0;
    Intensity intensity_;
    node *first = nullptr;
    node *last = nullptr;

    void del_next(node*);
    bool checkNext(node*);
    bool check(node*);
    void delFirst();
};

class usualGroupCourse : public NonIndividual {
  public:
    usualGroupCourse(Language, Level);
};

class supportiveGroupCourse : public NonIndividual {
  public:
    supportiveGroupCourse(Language, Level);
};

class intensiveGroupCourse : public NonIndividual {
  public:
    intensiveGroupCourse(Language, Level);
};

class Individual : public Group {
  public:
    Individual(Language, Level, Intensity, Consumer*);

    Consumer* get_consumer();
    Intensity get_intensity();

  private:
    Consumer* consumer_;
    Intensity intensity_;
};

class Course {
  public:
    Course() = default;

    void addPeople(const std::vector<Consumer*>&, const std::vector<Language>&,
            const std::vector<Level>&, const std::vector<Intensity>&);
    void recount();
    std::vector<NonIndividual*> get_non_individual();

    ~Course();
  private:
    std::vector<NonIndividual*> groups_;
    std::vector<Individual*> individuals_;
    int amountOfGroups{};
    void addGroup(NonIndividual* group);
    void deleteGroup(NonIndividual* group);
};

//Language sLanguage (int i);
//Level sLevel (int i);
//Intensity sIntencity (int i);
//void Modeling ();
class Modeling {
  public:
    Modeling() = default;
    void next() {};
    void addLang(const Language&);
    void setPeriod(const int&);
    [[nodiscard]] const std::vector<Language>& getLangs() const;
  private:
    std::vector<Language> languages_{};
    std::vector<Course*> consumers_{};
    void generate();
    int month_{};
};

}
