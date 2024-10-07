#include "../include/Application.h"
#include "../include/Modeling.h"
#include "../include/Canvas.h"

Window::Window(QWidget* w)
        : QMainWindow(w) {
    objects["Canvas"] = new Canvas(this, 1);
    objects["Canvas"]->show();
    this->setGeometry({0, 0, 1000, 1000});
}

