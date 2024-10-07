#include "../include/Drawable.h"

sf::Student::Student(Md::Consumer& me)
        : QWidget(nullptr), sf::CircleShape(10), me_(&me) { }

void sf::Student::updatePos(const sf::Vector2f& pos) {
    purpose_ = pos;
}

void sf::Student::move() {
    if (purpose_ == std::nullopt) return;

}