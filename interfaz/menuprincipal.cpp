#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include <QMessageBox>

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);

    connect(ui->btnJugar, SIGNAL(clicked()), this, SIGNAL(jugarClicked()));
    connect(ui->btnCargarPartida, SIGNAL(clicked()), this, SIGNAL(cargarPartidaClicked()));
    connect(ui->btnCreditos, SIGNAL(clicked()), this, SIGNAL(creditosClicked()));
    connect(ui->btnSalir, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}
