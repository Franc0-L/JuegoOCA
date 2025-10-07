#include "menuconfiguracion.h"
#include "ui_menuconfiguracion.h"
#include <QMessageBox>

MenuConfiguracion::MenuConfiguracion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuConfiguracion)
{
    ui->setupUi(this);

    connect(ui->btnGuardar, SIGNAL(clicked()), this, SLOT(onGuardarClicked()));
    connect(ui->btnVolver, SIGNAL(clicked()), this, SIGNAL(volverClicked()));

    connect(ui->sliderGeneral, SIGNAL(valueChanged(int)), this, SLOT(onVolGeneral(int)));
    connect(ui->sliderSonido, SIGNAL(valueChanged(int)), this, SLOT(onVolSonido(int)));
    connect(ui->sliderMusica, SIGNAL(valueChanged(int)), this, SLOT(onVolMusica(int)));
}

MenuConfiguracion::~MenuConfiguracion()
{
    delete ui;
}

void MenuConfiguracion::onGuardarClicked(){
    emit configuracionGuardada(ui->sliderGeneral->value(), ui->sliderSonido->value(), ui->sliderMusica->value());

    QMessageBox::information(this, "Configuracion", "La configuracion se guardo correctamente");
    emit volverClicked();
}

void MenuConfiguracion::onVolGeneral(int valor){
    ui->lblValGeneral->setText(QString("%1%").arg(valor));
}

void MenuConfiguracion::onVolSonido(int valor){
    ui->lblValSonido->setText(QString("%1%").arg(valor));
}

void MenuConfiguracion::onVolMusica(int valor){
    ui->lblValMusica->setText(QString("%1%").arg(valor));
}
