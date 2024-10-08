#include "../include/Application.h"
#include "../include/Modeling.h"
#include "../include/Canvas.h"
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

Window::Window(QWidget* w)
        : QMainWindow(w) {
    data_window();

}

void Window::data_window() {
    this->setFixedSize({250, 300});

    auto* label = new QLabel(this);
    objects["month_label"] = label;
    label->setText("Input the month amount");
    label->setGeometry({25, 10, 150, 20});

    auto* sp = new QSpinBox(this);
    objects["month_spinbox"] = sp;
    sp->setMinimum(1);
    sp->setMaximum(12);
    sp->setValue(1);
    sp->setGeometry({185, 10, 40, 20});


    auto* lang_label = new QLabel(this);
    objects["lang_label"] = lang_label;
    lang_label->setText("Select languages:");
    lang_label->setGeometry({25, 50, 150, 20});

    auto* En_cb = new QCheckBox("English", this);
    objects["EnCb"] = En_cb;
    En_cb->setGeometry({30, 80, 150, 20});
    En_cb->setCheckState(Qt::CheckState::Checked);

    auto* Fr_cb = new QCheckBox("French", this);
    objects["FrCb"] = Fr_cb;
    Fr_cb->setGeometry({30, 110, 150, 20});
    Fr_cb->setCheckState(Qt::CheckState::Checked);

    auto* Gm_cb = new QCheckBox("German", this);
    objects["GmCb"] = Gm_cb;
    Gm_cb->setGeometry({30, 140, 150, 20});
    Gm_cb->setCheckState(Qt::CheckState::Checked);

    auto* Ja_cb = new QCheckBox("Japanese", this);
    objects["JaCb"] = Ja_cb;
    Ja_cb->setGeometry({30, 170, 150, 20});
    Ja_cb->setCheckState(Qt::CheckState::Checked);

    auto* Ch_cb = new QCheckBox("Chinese", this);
    objects["ChCb"] = Ch_cb;
    Ch_cb->setGeometry({30, 200, 150, 20});
    Ch_cb->setCheckState(Qt::CheckState::Checked);

    auto* Sp_cb = new QCheckBox("Spanish", this);
    objects["SpCb"] = Sp_cb;
    Sp_cb->setGeometry({30, 230, 150, 20});
    Sp_cb->setCheckState(Qt::CheckState::Checked);

    auto* btn = new QPushButton("next", this);
    objects["next"] = btn;
    btn->setGeometry({140, 260, 80, 30});
}

