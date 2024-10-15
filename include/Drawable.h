#pragma once

#include "Modeling.h"
#include <SFML/Graphics.hpp>
#include <QWidget>
#include "Utility.h"

namespace sf {

class CourseD : public QWidget, public sf::RectangleShape {
  public:
    CourseD() = default;
    explicit CourseD(Md::Course&);
  private:
    Md::Course* course_{};
};

class Student : public QWidget, public sf::CircleShape {
    Q_OBJECT
  public:
    Student() = default;
    explicit Student(Md::Consumer&);
    void move();
    void press(sf::RenderWindow&);
  signals:
    void pressed();
  public slots:
        void updatePos(const sf::Vector2f&);
  private:
    static float radius(const sf::Vector2f&);
    bool inside(sf::RenderWindow&);
    Md::Consumer* me_{};
    std::optional<sf::Vector2f> purpose_{};
    std::optional<sf::Vector2f> velocity_{};
    std::optional<sf::Vector2f> begin_{};
    Timer t_{};
};

}