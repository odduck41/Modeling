#pragma once
#include <QApplication>
#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <QTimer>
#include <QPushButton>
#include "Modeling.h"

class Window : public QMainWindow {
  Q_OBJECT

  public:
    explicit Window(QWidget*);
  private:
    std::map<std::string, QWidget*> objects;
};
