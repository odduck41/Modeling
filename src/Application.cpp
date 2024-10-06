#include "../include/Application.h"
#include "../include/Modeling.h"

Window::Window(QWidget* w)
        : QMainWindow(w) {

    objects["Canvas"] = new QSFMLCanvas(this, 100);
    objects["Canvas"]->show();
    this->setGeometry({0, 0, 1000, 1000});

}
