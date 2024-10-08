#include "../include/Canvas.h"

Canvas::Canvas(QWidget* p, int fr) : QSFMLCanvas(p, fr) {
    setGeometry({0, 0, 500, 500});
}

void Canvas::onInit() {
    this->setGeometry({0, 0, 500, 500});

}

void Canvas::onUpdate() {
    clear(sf::Color::White);

}
