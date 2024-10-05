#pragma once

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
    case Language::English: return 800;
    case Language::French:
    case Language::German: return 500;
    case Language::Japanese: return 400;
    case Language::Chinese:
    case Language::Spanish: return 700;
    default:return 0;
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

    int get_cost() {
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
    int cost_;
};

}
