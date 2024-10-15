#include "../include/Application.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window(nullptr);
    window.show();
    return QApplication::exec();
}
