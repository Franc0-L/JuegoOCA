#include "menujuego.h"
#include "ui_menujuego.h"
#include "../juego/juegooca.h"
#include "../juego/jugador.h"
#include "../juego/tablero.h"
#include "../juego/dado.h"
#include <QMessageBox>
#include <QTimer>

MenuJuego::MenuJuego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuJuego)
    , juego(nullptr)
{
    ui->setupUi(this);

    connect(ui->btnDado, SIGNAL(clicked()), this, SLOT(onDadoLanzado()));
    connect(ui->btnGuardar, SIGNAL(clicked()), this, SLOT(onGuardarPartida()));
    connect(ui->btnCargar, SIGNAL(clicked()), this, SLOT(onCargarPartida()));
    connect(ui->btnMenuPrincipal, SIGNAL(clicked()), this, SIGNAL(menuPrincipalClicked()));
}

MenuJuego::~MenuJuego()
{
    delete ui;
}

void MenuJuego::crearPartida(JuegoOCA* nuevoJuego){
    juego = nuevoJuego;
    actualizarInterfaz();
}

void MenuJuego::onDadoLanzado(){
    if (!juego || juego->getJuegoTerminado()) return;

    ui->btnDado->setEnabled(false);
}

void MenuJuego::onGuardarPartida(){
    if (juego){
        std::string archivo = "partida.dat";
        juego->guardarPartida(archivo);
        agregarAlHistorial("Partida guardada correctamente");
        QMessageBox::information(this, "Partida Guardada", "La partida se ha guardado correctamente.");
    }
}

void MenuJuego::onCargarPartida(){
    std::string archivo = "partida.dat";
    if (juego && juego->cargarPartida(archivo)){
        actualizarInterfaz();
        agregarAlHistorial("Partida cargada correctamente");
        QMessageBox::information(this, "Partida Cargada", "La partida se ha cargado correctamente.");
    } else{
        QMessageBox::warning(this, "Error", "No se pudo cargar la partida.");
    }
}

void MenuJuego::actualizarInterfaz(){
    if (!juego) return;
    actualizarInfoJugador();
    actualizarTablero();
    actualizarHistorial();
}

void MenuJuego::actualizarInfoJugador(){
    if (!juego) return;

    int jugadorActual = juego->getJugadorActual();
    Jugador &jugador = juego->getJugadorPorIndice(jugadorActual);
    int tamanioTablero = juego->getTablero().getTamanio();

    ui->lblJugadorActual->setText(QString::fromStdString(jugador.getNombre()));
    ui->lblTurno->setText(QString::number(juego->getTurno()));
    ui->lblTamanioTablero->setText(QString("Tablero: %1 casillas").arg(tamanioTablero));

    QString estado;
    switch(jugador.getEstado()){
    case Jugador::NORMAL: estado = "Normal"; break;
    case Jugador::EN_POZO: estado = "En Pozo"; break;
    case Jugador::EN_CARCEL: estado = "En Cárcel"; break;
    case Jugador::EN_POSADA: estado = "En Posada"; break;
    }
    ui->lblResultadoDado->setText(QString("Posicion: %1 | %2").arg(jugador.getPosicion()).arg(estado));
}

void MenuJuego::actualizarTablero(){
    if (!juego) return;
    // FALTA
}

void MenuJuego::actualizarHistorial(){
    // FALTA
}

void MenuJuego::agregarAlHistorial(const QString &mensaje){
    QString historial = ui->txtHistorial->toPlainText();
    historial = mensaje + "\n" + historial;
    ui->txtHistorial->setPlainText(historial);
}
