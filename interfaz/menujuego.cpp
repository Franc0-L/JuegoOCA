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

    // Indicaciones para los jugadores
    ui->btnDado->setToolTip("Lanzar el dado para moverte");
    ui->btnGuardar->setToolTip("Guardar la partida actual");
    ui->btnCargar->setToolTip("Cargar una partida guardada");
    ui->btnMenuPrincipal->setToolTip("Volver al menú principal");

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

    juego->siguienteTurno();
    int posicionFinal = jugadorAntes.getPosicion();


    QString movimiento = QString("%1: %2 -> %3").arg(nombreJugador).arg(posicionInicial).arg(posicionFinal);

    Casilla* casilla = juego->getTablero().getCasilla(posicionFinal);
    if (casilla && casilla->getTipo() != "Normal"){
        movimiento += QString(" (%1)").arg(casilla->getTipo());
    }

    agregarAlHistorial(movimiento);
    actualizarInterfaz();

    if (juego->getJuegoTerminado()){
        QString mensaje = QString("¡Felicidades %1!\n\n"
                                  "Has ganado el juego en el turno %2.\n"
                                  "¿Quieres volver al Menu Principal?")
                              .arg(nombreJugador)
                              .arg(juego->getTurno());

        QMessageBox::StandardButton respuesta;
        respuesta = QMessageBox::question(this, "¡Juego Terminado!", mensaje,
                                          QMessageBox::Yes | QMessageBox::No);

        if (respuesta == QMessageBox::Yes){
            emit menuPrincipalClicked();
        }
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

    QString color;
    QString estado;
    switch(jugador.getEstado()){
    case Jugador::NORMAL:
        estado = "Normal";
        color = "white";
        break;
    case Jugador::EN_POZO:
        estado = "En Pozo";
        color = "red";
        break;
    case Jugador::EN_CARCEL:
        estado = "En Cárcel";
        color = "orange";
        break;
    case Jugador::EN_POSADA:
        estado = "En Posada";
        color = "blue";
        break;
    }
    QString textoEstado = QString("Posición: %1 | %2")
                              .arg(jugador.getPosicion())
                              .arg(estado);

    ui->lblEstadoJugador->setText(textoEstado);

    // Mejor visibilidad de los estados
    QString estilo = QString("QLabel{ color: %1; font-size: 18px; font-weight: bold; }").arg(color);
    ui->lblEstadoJugador->setStyleSheet(estilo);
}

void MenuJuego::limpiarTablero()
{
    QLayout* layout = ui->frameTablero->layout();
    if (layout){
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr){
            if (item->widget()){
                delete item->widget();
            }
            delete item;
        }
    }
}

void MenuJuego::actualizarTablero(){
    if (!juego) return;

    limpiarTablero();

    const Tablero& tablero = juego->getTablero();
    int tamanio = tablero.getTamanio();

    // Configurar grid layout
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->frameTablero->layout());
    if (!gridLayout){
        gridLayout = new QGridLayout(ui->frameTablero);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(10, 10, 10, 10);
        gridLayout->setAlignment(Qt::AlignCenter);
        ui->frameTablero->setLayout(gridLayout);
    }

    // Diseño del tablero
    ui->frameTablero->setStyleSheet(
        "QFrame#frameTablero {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #8B4513, stop:0.5 #A0522D, stop:1 #8B4513);"
        "   border: 8px solid #5D4037;"
        "   border-radius: 15px;"
        "}"
    );

    // Calcular disposición del tablero
    int columnas = 9;
    int filas = (tamanio + columnas - 1) / columnas;

    // Crear todas las casillas
    for (int i = 1; i <= tamanio; ++i) {
        int fila = (i - 1) / columnas;
        int columna = (i - 1) % columnas;

        // Patrón de serpiente (alternar dirección por fila)
        if (fila % 2 == 1) {
            columna = columnas - 1 - columna;
        }

        crearCasilla(i, fila, columna);
    }
}

void MenuJuego::crearCasilla(int numero, int fila, int columna){
    if (!juego) return;

    const Tablero& tablero = juego->getTablero();
    Casilla* casilla = tablero.getCasilla(numero);
    if (!casilla) return;

    // Frame principal de la casilla
    QFrame* frame = new QFrame();
    frame->setMinimumSize(70, 55);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    frame->setFrameStyle(QFrame::Box);
    frame->setLineWidth(1);

    QString tipo = QString::fromStdString(casilla->getTipo());
    QString colorFondo = QString::fromStdString(casilla->getColor());

    frame->setStyleSheet(QString(
                             "QFrame {"
                             " background-color: %1;"
                             " border: 2px solid #4a4a4a;"
                             " border-radius: 8px;"
                             "}"
                             ).arg(colorFondo));

    // Layout vertical simple
    QVBoxLayout* layout = new QVBoxLayout(frame);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    layout->setAlignment(Qt::AlignCenter);

    // Número de casilla
    QLabel* lblNum = new QLabel(QString::number(numero), frame);
    lblNum->setAlignment(Qt::AlignCenter);
    lblNum->setStyleSheet("font-weight: bold; font-size: 15px; color: #000;");
    layout->addWidget(lblNum);

    // Tipo (solo si no es normal)
    if (tipo != "Normal") {
        QLabel* lblTipo = new QLabel(tipo, frame);
        lblTipo->setAlignment(Qt::AlignCenter);
        lblTipo->setStyleSheet("font-size: 15px; font-weight: bold; color: #333;");
        layout->addWidget(lblTipo);
    }

    // Jugadores en esta casilla
    QString jugadores = obtenerInfoJugadoresEnCasilla(numero);
    if (!jugadores.isEmpty()) {
        QLabel* lblJugadores = new QLabel(jugadores, frame);
        lblJugadores->setAlignment(Qt::AlignCenter);
        lblJugadores->setStyleSheet(
            "font-size: 9px; font-weight: bold;"
            "background-color: rgba(255,255,255,0.8);"
            "border-radius: 3px; padding: 1px;"
            );
        layout->addWidget(lblJugadores);
    }

    // Destacar casilla del jugador actual
    int jugadorActual = juego->getJugadorActual();
    Jugador& jugador = juego->getJugadorPorIndice(jugadorActual);
    if (jugador.getPosicion() == numero) {
        frame->setStyleSheet(QString(
                                 "QFrame {"
                                 " background-color: %1;"
                                 " border: 3px solid #FF0000;"
                                 " border-radius: 8px;"
                                 "}"
                                 ).arg(colorFondo));
    }

    // Agregar al grid layout
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->frameTablero->layout());
    if (gridLayout) {
        gridLayout->addWidget(frame, fila, columna);
    }
}

QString MenuJuego::obtenerInfoJugadoresEnCasilla(int numeroCasilla)
{
    if (!juego) return "";

    QStringList jugadoresEnCasilla;

    // Buscar todos los jugadores que están en esta casilla
    for (int i = 0; i < 4; ++i){
        try{
            Jugador& jugador = juego->getJugadorPorIndice(i);
            if (jugador.getPosicion() == numeroCasilla){
                // Diferentes colores/iconos para cada jugador
                QString color;
                switch (i){
                case 0: color = "🔴"; break; // Rojo
                case 2: color = "🟢"; break;
                case 3: color = "🟣"; break;
                default: color = "⚫"; break;
                }
                jugadoresEnCasilla.append(color);
            }
        } catch (...){
            // Si no hay mas jugadores
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
