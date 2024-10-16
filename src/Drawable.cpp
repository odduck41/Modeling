#include "../include/Drawable.h"

sf::Student::Student(Md::Consumer* me)
        : QWidget(nullptr), sf::CircleShape(6), me_(me) {}

void sf::Student::updatePos(const sf::Vector2f& pos) {
    purpose_ = pos;
    const auto dis = pos - this->getPosition();
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

void sf::Student::press(const sf::RenderWindow& w) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (inside(w)) {
            emit pressed();
        }
    }
}

bool sf::Student::inside(const sf::RenderWindow& w) const {
    const auto mouse =
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(w)) -
            (this->getPosition() + sf::Vector2f{this->getRadius(), this->getRadius()});

    return radius(mouse) <= this->getRadius() * this->getRadius();
}

float sf::Student::radius(const sf::Vector2f& from) {
    return from.x * from.x + from.y * from.y;
}

sf::CourseD::CourseD(Md::Course* c, const sf::Vector2f& position) : course_(c) {
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineThickness(5. / 3);
    this->setOutlineColor(sf::Color::White);
    this->setPosition(position);
    this->setSize({720. /3, 540. / 3});

    groups.resize(9);
    for (auto& i : groups) {
        i = new GroupD;
    }

    sf::Vector2f pos = this->getPosition();
    sf::Vector2f e = pos;
    for (auto& group : groups) {
        group->setPosition(pos);
        if (pos.x < e.x + 120.) {
            pos.x += 60.;
        } else {
            pos.x = e.x;
            pos.y += 60.;
        }
    }
}

std::vector<sf::GroupD*> sf::CourseD::getGroups() const {
    return groups;
}

sf::GroupD::GroupD() {
    this->setFillColor(sf::Color::Transparent);
    this->setOutlineThickness(5. / 3);
    this->setOutlineColor(sf::Color::White);
    this->setSize({180. / 3, 180. / 3});
}
