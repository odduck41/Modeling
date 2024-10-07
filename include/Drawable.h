#pragma once

#include "Modeling.h"
#include <SFML/Graphics.hpp>
#include <QWidget>

namespace sf {

//class Course : public QWidget, public sf::RectangleShape {
//  public:
//    Course();
//
//};

class Student : public QWidget, public sf::CircleShape {
    Q_OBJECT
  public:
    Student(Md::Consumer&);
    void move();
  signals:
        void pressed();
  public slots:
        void updatePos(const sf::Vector2f&);
  private:
    Md::Consumer* me_{};
    std::optional<sf::Vector2f> purpose_{};
};

}