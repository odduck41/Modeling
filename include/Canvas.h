#pragma once

#include "QSFMLCanvas.h"
#include "Drawable.h"

class Mouse {
  public:
    bool update(const sf::Vector2f&);
    [[nodiscard]] std::optional<sf::Vector2f> diff() const;
    void reset();
  private:
    std::optional<sf::Vector2f> last_{};
    std::optional<sf::Vector2f> now_{};
};

class Canvas : public QSFMLCanvas {
    Q_OBJECT
  public:
    Canvas(QWidget*, int = 1);
  protected:
    void move();
    void onInit() override;
    void onUpdate() override;
  private:
    sf::Student s{};
    std::map<std::string, sf::Shape*> objects;
    Mouse m_{};
};