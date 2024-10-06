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

//class QSFMLCanvas;

class Student : public QWidget, public sf::CircleShape {
    Q_OBJECT
  public:
    explicit Student(QWidget* p);
    void press();
    signals:
        void pressed();
  private:
    bool inside();
    Md::Consumer* me{};
};
//
//class QSFMLCanvas : public QWidget, public sf::RenderWindow {
//  Q_OBJECT
//
//  public:
//    explicit QSFMLCanvas(QWidget* parent = nullptr, int frameTime = 1);
//    ~QSFMLCanvas() override = default;
//  private:
//    void onInit();
//    void onUpdate();
//    QPaintEngine* paintEngine() const override;
//    void showEvent(QShowEvent*) override;
//    void paintEvent(QPaintEvent*) override;
//
//  private slots:
//    void onTimeout();
//
//  private:
//    QTimer m_timer;
//    bool m_initialized;
//    Student s;
//};
