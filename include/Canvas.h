#pragma once

#include "QSFMLCanvas.h"

class Canvas : public QSFMLCanvas {
    Q_OBJECT
  public:
    Canvas(QWidget*, int);
  protected:
    void onInit() override;
    void onUpdate() override;
  private:

};