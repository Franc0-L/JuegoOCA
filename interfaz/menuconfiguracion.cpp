#include "menuconfiguracion.h"
#include "ui_menuconfiguracion.h"

MenuConfiguracion::MenuConfiguracion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuConfiguracion)
{
    ui->setupUi(this);
}

MenuConfiguracion::~MenuConfiguracion()
{
    delete ui;
}
