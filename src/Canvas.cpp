#include "../include/Canvas.h"
#include <ranges>

sf::Vector2f operator* (const sf::Vector2f& a, float b) {
    return {a.x * b, a.y * b};
}

Canvas::Canvas(QWidget* p, int fr) : QSFMLCanvas(p, fr) {
    this->setGeometry({200, 0, 600, 600});
}

void Canvas::onInit() {
    auto* a = new sf::CircleShape(50);
    a->setPosition(250, 250);
    a->setFillColor(sf::Color::Black);
    objects["e"] = a;
}

void Canvas::onUpdate() {
    clear(sf::Color::White);
    move();
    draw(*dynamic_cast<sf::CircleShape*>(objects["e"]));
}

void Canvas::move() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (m_.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this)))) {
            for (auto& i : objects | std::views::values) {
                i->move(m_.diff().value_or(sf::Vector2f{0, 0}));
            }
        }
    } else {
        m_.reset();
    }
}

bool Mouse::update(const sf::Vector2f& nw) {
    auto diff_ = now_.value_or(sf::Vector2f{0, 0}) - last_.value_or(sf::Vector2f{0, 0});
    if (last_ == std::nullopt) {
        last_ = nw;
        return false;
    }
    if (now_ != std::nullopt) {
        last_ = now_;
    }
    now_ = nw;
    return diff_ != now_.value() - last_.value();
}

std::optional<sf::Vector2f> Mouse::diff() const {
    if (now_ == std::nullopt || last_ == std::nullopt) return {};
    return now_.value() - last_.value();
}

void Mouse::reset() {
    now_ = std::nullopt;
    last_ = std::nullopt;
}

