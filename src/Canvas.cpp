#include "../include/Canvas.h"

Canvas::Canvas(QWidget* p, int fr) : QSFMLCanvas(p, fr) {
    setGeometry({0, 0, 500, 500});
}

void Canvas::onInit() {
    this->setGeometry({0, 0, 500, 500});
    s.setPosition(200, 200);
    s.setRadius(50);
    s.setFillColor(sf::Color::Black);
    auto _ = connect(&s, &sf::Student::pressed, [this]() {
        s.updatePos(s.getPosition() + sf::Vector2f{50, 50});
    });
}

void Canvas::onUpdate() {
    clear(sf::Color::White);

    s.press(*this);
    s.move();

    draw(s);
}
