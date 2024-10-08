#pragma once

#include "QSFMLCanvas.h"
#include "Drawable.h"

class Canvas : public QSFMLCanvas {
    Q_OBJECT
  public:
    Canvas(QWidget*, int);
  protected:
    void onInit() override;
    void onUpdate() override;
  private:
    sf::Student s{};
};