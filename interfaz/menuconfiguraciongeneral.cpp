#include "menuconfiguraciongeneral.h"
#include "ui_menuconfiguraciongeneral.h"

MenuConfiguracionGeneral::MenuConfiguracionGeneral(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuConfiguracionGeneral)
{
    ui->setupUi(this);
}

MenuConfiguracionGeneral::~MenuConfiguracionGeneral()
{
    delete ui;
}
