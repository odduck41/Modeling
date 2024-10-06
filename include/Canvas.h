#pragma once

#include "QSFMLCanvas.h"

class Canvas : public QSFMLCanvas {
    Q_OBJECT
  protected:
    void onInit() override;
    void onUpdate() override;

};