#include "menujuego.h"
#include "ui_menujuego.h"
#include "../juego/juegooca.h"
#include "../juego/jugador.h"
#include "../juego/tablero.h"
#include <QMessageBox>

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
    ui->txtHistorial->clear();
    actualizarInterfaz();
}

void MenuJuego::onDadoLanzado(){
    if (!juego || juego->getJuegoTerminado()) return;

    int indiceJugador = juego->getJugadorActual();
    Jugador& jugadorAntes = juego->getJugadorPorIndice(indiceJugador);
    int posicionInicial = jugadorAntes.getPosicion();
    QString nombreJugador = QString::fromStdString(jugadorAntes.getNombre());

    // Ejecutar turno
    juego->siguienteTurno();
    int posicionFinal = jugadorAntes.getPosicion();

    // Agregar al historial
    QString movimiento = QString("%1: %2 -> %3").arg(nombreJugador).arg(posicionInicial).arg(posicionFinal);

    // Verificar si hubo efecto especial
    Casilla* casilla = juego->getTablero().getCasilla(posicionFinal);
    if (casilla && casilla->getTipo() != "Normal") {
        movimiento += QString(" (%1)").arg(casilla->getTipo());
    }

    agregarAlHistorial(movimiento);
    actualizarInterfaz();

    // Verificar si el juego terminó
    if (juego->getJuegoTerminado()) {
        QMessageBox::information(this, "Juego Terminado", QString("%1 ha ganado el juego!").arg(nombreJugador));
    }
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
        ui->txtHistorial->clear();
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
    ui->lblEstadoJugador->setText(QString("Posicion: %1 | %2").arg(jugador.getPosicion()).arg(estado));
}

void MenuJuego::actualizarTablero(){
    if (!juego) return;
    // FALTA
}

void MenuJuego::actualizarHistorial(){
    if (!juego) return;

    // Mostrar información del turno actual
    QString infoTurno = QString("TURNO %1").arg(juego->getTurno());
    if (ui->txtHistorial->toPlainText().isEmpty() || !ui->txtHistorial->toPlainText().contains(infoTurno)){
        agregarAlHistorial(infoTurno);
    }
}

void MenuJuego::agregarAlHistorial(const QString &mensaje){
    QString historial = ui->txtHistorial->toPlainText();
    historial = mensaje + "\n" + historial;
    ui->txtHistorial->setPlainText(historial);
}
