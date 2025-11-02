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
    connect(ui->btnReglas, SIGNAL(clicked()), this, SLOT(reglasClicked()));
    connect(ui->btnSalir, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::reglasClicked()
{
    QString reglas =
        "🎯 REGLAS DEL JUEGO DE LA OCA 🎯\n\n"

        "📋 REGLAS GENERALES:\n"
        "• Cada jugador lanza el dado en su turno y avanza su ficha\n"
        "• Gana el primero que llegue EXACTAMENTE a la casilla 63\n"
        "• Si sacas más puntos de los necesarios, debes retroceder\n"
        "• El juego sigue hasta que un jugador gane\n\n"

        "🦢 CASILLAS ESPECIALES - OCAS:\n"
        "• Casillas: 9, 18, 27, 36, 45, 54\n"
        "• Efecto: 'De oca a oca y tiro porque me toca'\n"
        "• Avanzas a la siguiente oca y vuelves a tirar\n\n"

        "🌉 CASILLA PUENTE:\n"
        "• Casilla: 6\n"
        "• Efecto: 'Del puente a la posada'\n"
        "• Avanzas a la casilla 12\n\n"

        "🏠 CASILLA POSADA:\n"
        "• Casilla: 19\n"
        "• Efecto: Pierdes 1 turno\n\n"

        "⚠️ CASILLA POZO:\n"
        "• Casilla: 31\n"
        "• Efecto: No puedes moverte hasta que otro jugador caiga en la misma casilla\n\n"

        "🌀 CASILLA LABERINTO:\n"
        "• Casilla: 42\n"
        "• Efecto: Retrocedes hasta la casilla 30\n\n"

        "🔒 CASILLA CÁRCEL:\n"
        "• Casilla: 56\n"
        "• Efecto: Pierdes 2 turnos\n\n"

        "💀 CASILLA CALAVERA:\n"
        "• Casilla: 58\n"
        "• Efecto: Vuelves a la casilla 1 (¡Comienzas de nuevo!)\n\n"

        "🌸 CASILLA JARDÍN DE LA OCA:\n"
        "• Casilla: 63\n"
        "• Efecto: ¡Ganas el juego si llegas exactamente!\n\n"

        "🎲 REGLAS ESPECIALES DEL DADO:\n"
        "• Con 1 dado: Avanzas el número que salga (1-6)\n"
        "• Con 2 dados: Se suman ambos dados para el avance\n"
        "• Si los dados son consecutivos (ej: 3-4, 4-5): +1 punto extra\n"
        "• Si los dados son dobles (ej: 3-3, 5-5): +2 puntos extra\n\n"

        "⚙️ CONFIGURACIONES ESPECIALES:\n"
        "• Puedes jugar con 1 o 2 dados\n"
        "• Tablero personalizable de 63 a 90 casillas\n"
        "• Guardado y carga de partidas";

    QMessageBox::information(this, "Reglas del Juego de la Oca", reglas);
}
