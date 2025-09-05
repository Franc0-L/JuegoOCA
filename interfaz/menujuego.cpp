#include "menujuego.h"
#include "ui_menujuego.h"

MenuJuego::MenuJuego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuJuego)
{
    ui->setupUi(this);
}

MenuJuego::~MenuJuego()
{
    delete ui;
}
