#include "../include/Canvas.h"
#include "../include/Drawable.h"
#include <ranges>

sf::Vector2f operator* (const sf::Vector2f& a, float b) {
    return {a.x * b, a.y * b};
}

Canvas::Canvas(QWidget* p, Md::Modeller* md, int fr)
: QSFMLCanvas(p, fr), md_(md) {
    this->setGeometry({200, 0, 600, 600});
}

void Canvas::onInit() {
    // objects["Course"] = new sf::CourseD(new Md::Course(Md::Language::English),
    //     {10., 10.});
    long long o = 0;
    for (auto& i : md_->get_courses()) {
        objects["Course" + std::to_string(o)] =  new sf::CourseD(new Md::Course(Md::Language::English),
        {10.f + (720.f / 3 + 20) * (o / 3), 10.f + (540.f / 3 + 20) * (o % 3)});
        long long index = 0;
        for (const auto& group:
            dynamic_cast<sf::CourseD*>(objects["Course" + std::to_string(o)])
            ->getGroups()) {
            auto e = group->getPosition();
            objects["Group" + std::to_string(o) + std::to_string(index++)] = group;

        }
        ++o;
    }

}

void Canvas::onUpdate() {
    clear(sf::Color::Black);
    if (this->QWidget::hasFocus()) {
        move();
    } else {
        m_.reset();
    }

    for (auto& i : objects | std::views::values) {
        draw(*i);
    }
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

