#include "Application.h"
#include "Modeling.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>


Window::Window(QWidget* w)
        : QMainWindow(w) {
    objects["Canvas"] = new QSFMLCanvas(this, 100);
    objects["Canvas"]->show();
    this->setGeometry({0, 0, 1000, 1000});
}

QSFMLCanvas::QSFMLCanvas(QWidget* parent, int frameTime)
        : QWidget(parent), m_initialized(false) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);


    setFocusPolicy(Qt::StrongFocus);

    m_timer.setInterval(frameTime);
    setGeometry({0, 0, 500, 500});
}

void QSFMLCanvas::onInit() {
    s.setFillColor(sf::Color::Green);
    s.setPosition(250, 250);
    s.setSize({50, 50});
    connect(&s, &Something::pressed, [=]() {
       qDebug() << "Pressed";
    });

}

void QSFMLCanvas::onUpdate() {
    sf::Event event{};
    if (this->pollEvent(event)) {
        ;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto pos = sf::Mouse::getPosition(*this);
        auto s_pos = s.getPosition();
        auto s_w = s_pos + s.getSize();
        if (s_pos.x <= pos.x && pos.x <= s_w.x && s_pos.y <= pos.y && pos.y <= s_w.y) {
            emit s.pressed();
        }
//        qDebug() << pos.x << " " << pos.y;
    }

    clear(sf::Color::White);

    draw(s);
}

QPaintEngine* QSFMLCanvas::paintEngine() const {
    return nullptr;
}

void QSFMLCanvas::showEvent(QShowEvent*) {
    if (!m_initialized) {

        RenderWindow::create(sf::WindowHandle(winId()));
        onInit();

        auto e =
                connect(&m_timer, &QTimer::timeout, this, &QSFMLCanvas::onTimeout);

        m_timer.start();
        m_initialized = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*) {
    onUpdate();

    display();
}

void QSFMLCanvas::onTimeout() {
    repaint();
}