#pragma once

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow {
  Q_OBJECT

  public:
    explicit QSFMLCanvas(QWidget* = nullptr, int = 1);
    ~QSFMLCanvas() override = default;
  protected:
    virtual void onInit() = 0;
    virtual void onUpdate() = 0;

    QPaintEngine* paintEngine() const override;
    void showEvent(QShowEvent*) override;
    void paintEvent(QPaintEvent*) override;

  private slots:
    void onTimeout();

  private:
    QTimer timer_{};
    bool is_init{};
};
