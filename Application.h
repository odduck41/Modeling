#pragma once
#include <QApplication>
#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <QTimer>
#include <QPushButton>

class Window : public QMainWindow {
  Q_OBJECT

  public:
    explicit Window(QWidget*);
  private:
    std::map<std::string, QWidget*> objects;
};

struct Something : public QWidget, public sf::RectangleShape {
  Q_OBJECT
  signals:
    void pressed();
};

class QSFMLCanvas : public QWidget, public sf::RenderWindow {
  Q_OBJECT

  public:
    explicit QSFMLCanvas(QWidget* parent = nullptr, int frameTime = 50);
    ~QSFMLCanvas() override = default;

  private:
    void onInit();
    void onUpdate();
    virtual QPaintEngine* paintEngine() const override;
    virtual void showEvent(QShowEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;

  private slots:
    void onTimeout();

  private:
    QTimer m_timer;
    bool m_initialized;

    Something s;
};
