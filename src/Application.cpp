#include "../include/Application.h"
#include "../include/Modeling.h"

Window::Window(QWidget* w)
        : QMainWindow(w) {

    objects["Canvas"] = new QSFMLCanvas(this, 100);
    objects["Canvas"]->show();
    this->setGeometry({0, 0, 1000, 1000});

}

//QSFMLCanvas::QSFMLCanvas(QWidget* parent, int frameTime)
//        : QWidget(parent), m_initialized(false), s(this) {
//    setAttribute(Qt::WA_PaintOnScreen);
//    setAttribute(Qt::WA_OpaquePaintEvent);
//    setAttribute(Qt::WA_NoSystemBackground);
//
//    setFocusPolicy(Qt::StrongFocus);
//
//    m_timer.setInterval(frameTime);
//    setGeometry({200, 0, 800, 800});
//}
//
//void QSFMLCanvas::onInit() {
//    setActive(true);
//    s.setFillColor(sf::Color::Black);
//    s.setPosition(250, 250);
//    s.setRadius(50);
//    auto _ = connect(&s, &Student::pressed, [this]() {
//      static int r = 0;
//      static int g = 0;
//      static int b = 0;
//      (r += 15) %= 257;
//      (g += 25) %= 257;
//      (b += 30) %= 257;
//      s.setFillColor(sf::Color(r, g, b));
//    });
//
//}
//
//void QSFMLCanvas::onUpdate() {
//    setActive(true);
//    sf::Event event{};
//    if (this->pollEvent(event)) {
//        s.press();
//    }
//
//    clear(sf::Color::White);
//
//    draw(s);
//}
//
//QPaintEngine* QSFMLCanvas::paintEngine() const {
//    return nullptr;
//}
//
//void QSFMLCanvas::showEvent(QShowEvent*) {
//    setActive(true);
//    if (!m_initialized) {
//        RenderWindow::create(sf::WindowHandle(winId()));
//
//        setActive(true);
//        onInit();
//
//        auto _ =
//                connect(&m_timer, &QTimer::timeout, this, &QSFMLCanvas::onTimeout);
//
//        m_timer.start();
//        m_initialized = true;
//    }
//}
//
//void QSFMLCanvas::paintEvent(QPaintEvent*) {
//    setActive(true);
//    onUpdate();
//
//    display();
//}
//
//void QSFMLCanvas::onTimeout() {
//    setActive(true);
//    repaint();
//}

Student::Student(QWidget* p)
        : QWidget(p) {
    me = nullptr;
}

void Student::press() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (inside()) {
            emit pressed();
        }
    }
}

bool Student::inside() {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(
            dynamic_cast<sf::RenderWindow&>(*this->parent())));

    mousePos -= this->getPosition() + sf::Vector2f{this->getRadius(), this->getRadius()};
    return mousePos.x * mousePos.x + mousePos.y * mousePos.y <= this->getRadius() * this->getRadius();
}
