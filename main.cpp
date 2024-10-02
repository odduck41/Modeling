#include <iostream>
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
int main() {
    Group(English, Mid, 1);
    return 0;
}
