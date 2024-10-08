#include "../include/Drawable.h"

sf::Student::Student(Md::Consumer& me)
        : QWidget(nullptr), sf::CircleShape(10), me_(&me) {}

void sf::Student::updatePos(const sf::Vector2f& pos) {
    purpose_ = pos;
    auto dis = this->getPosition() - pos;
    t_.reset();
    t_.updateDifference(500ms);
    velocity_ = {dis.x / 500, dis.y / 500};
}

void sf::Student::move() {
    if (purpose_ == std::nullopt || !t_.lasted()) return;
    this->setPosition(this->getPosition() + velocity_.value());

    if (this->getPosition() == purpose_) {
        purpose_ = std::nullopt;
        velocity_ = std::nullopt;
    }
}

void sf::Student::press(sf::RenderWindow& w) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (inside(w)) {
            emit pressed();
        }
    }
}

bool sf::Student::inside(sf::RenderWindow& w) {
    auto mouse =
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(w)) - this->getPosition();
    return mouse.x * mouse.x + mouse.y * mouse.y <= this->getRadius() * this->getRadius();
}
