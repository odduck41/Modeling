#include "../include/QSFMLCanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget* parent, int FrameRate)
        : QWidget(parent), is_init(false) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    timer_.setInterval(FrameRate);
}

QPaintEngine* QSFMLCanvas::paintEngine() const {
    return nullptr; // Qt won't paint something itself
}

void QSFMLCanvas::showEvent(QShowEvent*) {
    if (!is_init) {
        RenderWindow::create(sf::WindowHandle(winId()));
        onInit();

        auto _ =
                connect(&timer_, &QTimer::timeout, this, &QSFMLCanvas::onTimeout);

        timer_.start();

        is_init = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*) {
    onUpdate();

    display();
}

void QSFMLCanvas::onTimeout() {
    repaint();
}



