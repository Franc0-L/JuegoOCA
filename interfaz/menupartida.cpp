#include "menupartida.h"
#include "ui_menupartida.h"

MenuPartida::MenuPartida(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPartida)
{
    ui->setupUi(this);

    connect(ui->comboJugadores, SIGNAL(currentIndexChanged(int)), this, SLOT(onNumJugadores()));
    connect(ui->btnComenzarPartida, SIGNAL(clicked()), this, SLOT(onComenzarClicked()));
    connect(ui->btnCancelarPartida, SIGNAL(clicked()), this, SLOT(onCancelarClicked()));
    connect(ui->checkPersonalizado, SIGNAL(toggled(bool)), ui->spinTamTablero, SLOT(setEnabled(bool)));

    ui->spinTamTablero->setEnabled(ui->checkPersonalizado->isChecked());
    onNumJugadores();
}

MenuPartida::~MenuPartida()
{
    delete ui;
}

void MenuPartida::onNumJugadores(){
    actualizarInfoJugadores();
}

void MenuPartida::onComenzarClicked(){
    int numJugadores = ui->comboJugadores->currentText().toInt();
    int tamTablero = ui->spinTamTablero->value();
    bool personalizado = ui->checkPersonalizado->isChecked();
    bool dosDados = ui->checkDosDados->isChecked();

    std::vector<std::string> nombres;
    nombres.push_back(ui->editJugador1->text().toStdString());
    nombres.push_back(ui->editJugador2->text().toStdString());

    if (numJugadores >= 3) {
        nombres.push_back(ui->editJugador3->text().toStdString());
    }
    if (numJugadores >= 4) {
        nombres.push_back(ui->editJugador4->text().toStdString());
    }

    emit comenzarPartida(numJugadores, nombres, tamTablero, personalizado, dosDados);
}

void MenuPartida::onCancelarClicked(){
    emit cancelarClicked();
}

void MenuPartida::actualizarInfoJugadores(){
    QString texto = ui->comboJugadores->currentText();
    int numJugadores = texto.toInt();

    // Mostrar/ocultar campos según el número de jugadores
    bool mostrarJugador3 = (numJugadores >= 3);
    bool mostrarJugador4 = (numJugadores >= 4);

    ui->editJugador3->setVisible(mostrarJugador3);
    ui->lblJugador3->setVisible(mostrarJugador3);
    ui->editJugador4->setVisible(mostrarJugador4);
    ui->lblJugador4->setVisible(mostrarJugador4);
}
