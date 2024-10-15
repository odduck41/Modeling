#pragma once
#include <string>
#include <random>
#include <vector>
#include <tuple>
#include <map>
#include <list>
#include <set>

enum Level {
  Low = 1,
  Middle = 2,
  Advanced = 3
};

enum Intensity {
  usual = 1,
  supportive = 2,
  intensive = 3
};

enum Language {
  English = 1,
  French = 2,
  German,
  Japanese,
  Chinese,
  Spanish
};

struct Data {
  explicit Data(const Language& language);
  Data() = delete;
  Language language_{};
  Level level_{};
  Intensity intensity_{};
};

class Lesson {
  public:
    explicit Lesson(const Data&);
    [[nodiscard]] Language getLanguage() const;
    [[nodiscard]] Intensity getIntensity() const;
    [[nodiscard]] Level getLevel() const;
    [[nodiscard]] long long getCost() const;
    virtual void update() = 0;
    virtual ~Lesson() = 0;
  protected:
    Data data_;
};

class Course;

class Consumer {
  public:
    explicit Consumer(const std::vector<Data>&);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getSurname() const;
    [[nodiscard]] bool alive() const;
    void update(const Language& );
    static bool rejected(const bool&);
    static bool pay(const long long&);
  private:
    std::set<Language> courses_;
    static void parse();
    static std::vector<std::string> names_;
    static std::vector<std::string> surnames_;
    std::string name_;
    std::string surname_;
    std::vector<Data> data_;
};

struct Application {
  explicit Application(const std::vector<Language>&);
  Consumer* consumer{};
  std::vector<Data> data;
};

class Individual : public Lesson {
  public:
    Individual(const Data&, Consumer*);
    [[nodiscard]] Consumer* who() const;
    void update() override;
  private:
    Consumer* consumer_{};
};

class Group : public Lesson {
  public:
    explicit Group(const Data&);
    void add(Consumer*);
    void update() override;
    [[nodiscard]] bool full() const;
  private:
    std::list<Consumer*> consumers_;
};

class Course {
  public:
    explicit Course(const Language&);
    void add(Application*);
    void reorder();
  private:
    std::map<Data, Group*> groups_;
    std::vector<Individual*> individual_;
    Language language_;
};
