#include "menuconfiguracionpartida.h"
#include "ui_menuconfiguracionpartida.h"

MenuConfiguracionPartida::MenuConfiguracionPartida(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuConfiguracionPartida)
{
    ui->setupUi(this);
}

MenuConfiguracionPartida::~MenuConfiguracionPartida()
{
    delete ui;
}
