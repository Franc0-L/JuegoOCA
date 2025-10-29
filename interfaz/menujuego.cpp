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

    limpiarTablero();

    const Tablero& tablero = juego->getTablero();
    int tamanio = tablero.getTamanio();

    // Configurar grid layout si no existe
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->frameTablero->layout());
    if (!gridLayout) {
        gridLayout = new QGridLayout(ui->frameTablero);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        ui->frameTablero->setLayout(gridLayout);
    }

    // Calcular disposición del tablero
    int columnas = 8; // Número fijo de columnas
    int filas = (tamanio + columnas - 1) / columnas; // Redondeo hacia arriba

    // Crear todas las casillas
    for (int i = 1; i <= tamanio; ++i) {
        int fila = (i - 1) / columnas;
        int columna = (i - 1) % columnas;

        crearCasilla(i, fila, columna);
    }
}

void MenuJuego::limpiarTablero()
{
    QLayout* layout = ui->frameTablero->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    }
}

void MenuJuego::crearCasilla(int numero, int fila, int columna)
{
    if (!juego) return;

    const Tablero& tablero = juego->getTablero();
    Casilla* casilla = tablero.getCasilla(numero);
    if (!casilla) return;

    // Crear frame de la casilla
    QFrame* casillaFrame = new QFrame();
    casillaFrame->setMinimumSize(75, 55);
    casillaFrame->setMaximumSize(75, 55);
    casillaFrame->setFrameStyle(QFrame::Box);
    casillaFrame->setLineWidth(2);

    // Layout vertical para la casilla
    QVBoxLayout* layoutCasilla = new QVBoxLayout(casillaFrame);
    layoutCasilla->setContentsMargins(2, 2, 2, 2);
    layoutCasilla->setSpacing(1);
    layoutCasilla->setAlignment(Qt::AlignCenter);

    // Número de casilla
    QLabel* labelNumero = new QLabel(QString::number(numero));
    labelNumero->setAlignment(Qt::AlignCenter);
    labelNumero->setStyleSheet("font-weight: bold; font-size: 10px; color: #000000;");
    labelNumero->setMinimumHeight(12);
    layoutCasilla->addWidget(labelNumero);

    // Tipo de casilla (si no es normal)
    QString tipo = QString::fromStdString(casilla->getTipo());
    if (tipo != "Normal") {
        QLabel* labelTipo = new QLabel(tipo);
        labelTipo->setAlignment(Qt::AlignCenter);
        labelTipo->setStyleSheet("font-size: 8px; font-weight: bold; color: #000000;");
        labelTipo->setMinimumHeight(10);
        layoutCasilla->addWidget(labelTipo);
    }

    // Información de jugadores en esta casilla
    QString jugadoresInfo = obtenerInfoJugadoresEnCasilla(numero);
    if (!jugadoresInfo.isEmpty()) {
        QLabel* labelJugadores = new QLabel(jugadoresInfo);
        labelJugadores->setAlignment(Qt::AlignCenter);
        labelJugadores->setStyleSheet("font-size: 9px; font-weight: bold; "
                                      "background-color: rgba(255,255,255,0.8); "
                                      "border-radius: 3px; padding: 1px;");
        labelJugadores->setMinimumHeight(12);
        layoutCasilla->addWidget(labelJugadores);
    }

    // Agregar al grid layout
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->frameTablero->layout());
    if (gridLayout) {
        gridLayout->addWidget(casillaFrame, fila, columna);
    }
}

QString MenuJuego::obtenerInfoJugadoresEnCasilla(int numeroCasilla)
{
    if (!juego) return "";

    QStringList jugadoresEnCasilla;

    // Buscar todos los jugadores que están en esta casilla
    for (int i = 0; i < 4; ++i) {
        try {
            Jugador& jugador = juego->getJugadorPorIndice(i);
            if (jugador.getPosicion() == numeroCasilla) {
                // Usar diferentes colores/iconos para cada jugador
                QString color;
                switch (i) {
                case 0: color = "🔴"; break; // Rojo
                case 1: color = "🔵"; break; // Azul
                case 2: color = "🟢"; break; // Verde
                case 3: color = "🟣"; break; // Morado
                default: color = "⚫"; break; // Negro
                }
                jugadoresEnCasilla.append(color);
            }
        } catch (...) {
            // Jugador no existe, continuar
            break;
        }
    }

    return jugadoresEnCasilla.join(" ");
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
