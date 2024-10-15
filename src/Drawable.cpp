#include "../include/Drawable.h"

sf::Student::Student(Md::Consumer* me)
        : QWidget(nullptr), sf::CircleShape(10), me_(me) {}

void sf::Student::updatePos(const sf::Vector2f& pos) {
    purpose_ = pos;
    auto dis = pos - this->getPosition();
    t_.reset();
    t_.updateDifference(500ms);
    velocity_ = {dis.x / 500, dis.y / 500};
    begin_ = this->getPosition();
}

void sf::Student::move() {
    if (purpose_ == std::nullopt || !t_.lasted()) return;
    this->setPosition(this->getPosition() + velocity_.value());

    if (radius(this->getPosition() - begin_.value()) >= radius(purpose_.value() - begin_.value())) {
        this->setPosition(purpose_.value());
        purpose_ = std::nullopt;
        velocity_ = std::nullopt;
        begin_ = std::nullopt;
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
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(w)) -
            (this->getPosition() + sf::Vector2f{this->getRadius(), this->getRadius()});

    return radius(mouse) <= this->getRadius() * this->getRadius();
}

float sf::Student::radius(const sf::Vector2f& from) {
    return from.x * from.x + from.y * from.y;
}

sf::CourseD::CourseD(Md::Course* c) : course_(c) {
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineThickness(5.);
    this->setOutlineColor(sf::Color::Black);
    this->setPosition(0, 0);
    this->setSize({720, 540});

    groups.resize(9);
    for (auto& i : groups) {
        i = new GroupD;
    }

    sf::Vector2f pos = this->getPosition();
    for (auto& group : groups) {
        group->setPosition(pos);
        if (pos.y < 360) {
            pos.y += 180;
        } else {
            pos.y = 0;
            pos.x += 180;
        }
    }
}

std::vector<sf::GroupD*> sf::CourseD::getGroups() const {
    return groups;
}

sf::GroupD::GroupD() {
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineThickness(5.);
    this->setOutlineColor(sf::Color::Black);
    this->setSize({180, 180});
}
