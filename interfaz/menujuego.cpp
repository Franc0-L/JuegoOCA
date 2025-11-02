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
        std::string archivo = "../../guardado/partida.dat";
        std::string configuracion = "../../guardado/configuracion.txt";
        juego->guardarConfiguracion(configuracion);
        juego->guardarPartida(archivo);
        agregarAlHistorial("Partida guardada correctamente");
        QMessageBox::information(this, "Partida Guardada", "La partida se ha guardado correctamente.");
    }
}

void MenuJuego::onCargarPartida(){
    std::string archivo = "../../guardado/partida.dat";
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
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout->setAlignment(Qt::AlignCenter);
        ui->frameTablero->setLayout(gridLayout);
    }

    // Calcular disposición del tablero
    const int columnas = 9;
    int filas = (tamanio + columnas - 1) / columnas;
    int matriz[10][10] = {{0}};

    int arriba = 0, abajo = filas - 1;
    int izquierda = 0, derecha = columnas - 1;
    int num = 1;
    while (arriba <= abajo && izquierda <= derecha && num <= tamanio){
        // izquierda a derecha
        for (int j = izquierda; j <= derecha && num <= tamanio; ++j) matriz[arriba][j] = num++;
        arriba++;

        // arriba a abajo
        for (int i = arriba; i <= abajo && num <= tamanio; ++i) matriz[i][derecha] = num++;
        derecha--;

        // derecha a izquierda
        for (int j = derecha; j >= izquierda && num <= tamanio; --j) matriz[abajo][j] = num++;
        abajo--;

        // abajo a arriba
        for (int i = abajo; i >= arriba && num <= tamanio; --i) matriz[i][izquierda] = num++;
        izquierda++;
    }

    // Casillas segun la matriz del tablero
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j){
            int numCasilla = matriz[i][j];
            if (numCasilla > 0 && numCasilla <= tamanio) crearCasilla(numCasilla, i, j);
        }
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
                             " border: 1px #4a4a4a;"
                             " border-radius: 8px;"
                             "}"
                             ).arg(colorFondo));

    // Configuracion layout de las casillas
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(frame);
    layoutPrincipal->setContentsMargins(4, 4, 4, 4);
    layoutPrincipal->setSpacing(2);

    QHBoxLayout* layoutSuperior = new QHBoxLayout();
    layoutSuperior->setContentsMargins(0, 0, 0, 0);
    layoutSuperior->setSpacing(0);
    QLabel* lblNum = new QLabel(QString::number(numero), frame);
    lblNum->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblNum->setStyleSheet("font-weight: bold; font-size: 13px; color: #000;");
    layoutSuperior->addWidget(lblNum);
    layoutSuperior->addStretch();
    layoutPrincipal->addLayout(layoutSuperior);

    QLabel* lblTipo = new QLabel(tipo, frame);
    lblTipo->setAlignment(Qt::AlignCenter);
    if (tipo != "Normal") {
        lblTipo->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
    } else {
        lblTipo->setStyleSheet("font-size: 14px; font-weight: bold; color: #222;");
    }
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(lblTipo, 0, Qt::AlignCenter);
    layoutPrincipal->addStretch();

    QString jugadores = obtenerInfoJugadoresEnCasilla(numero);
    if (!jugadores.isEmpty()){
        QLabel* lblJugadores = new QLabel(jugadores, frame);
        lblJugadores->setAlignment(Qt::AlignCenter);
        lblJugadores->setStyleSheet(
            "font-size: 9px; font-weight: bold;"
            "background-color: rgba(255,255,255,0.8);"
            "border-radius: 3px; padding: 1px;"
            );
        layoutPrincipal->addWidget(lblJugadores, 0, Qt::AlignBottom | Qt::AlignCenter);
    }

    // Destacar jugador del turno actual
    int jugadorActual = juego->getJugadorActual();
    Jugador& jugador = juego->getJugadorPorIndice(jugadorActual);
    if (jugador.getPosicion() == numero) {
        frame->setStyleSheet(QString(
                                 "QFrame {"
                                 " background-color: %1;"
                                 " border: 3px solid #FF4444;"
                                 " border-radius: 8px;"
                                 "}"
                                 ).arg(colorFondo));
    }

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
