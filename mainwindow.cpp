#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "interfaz/menuprincipal.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , juego(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("Juego de la Oca");
    stackPantallas = new QStackedWidget(this);
    setCentralWidget(stackPantallas);

    menuPrincipal = new MenuPrincipal(this);
    menuPartida = new MenuPartida(this);
    menuJuego = new MenuJuego(this);

    stackPantallas->addWidget(menuPrincipal);
    stackPantallas->addWidget(menuPartida);
    stackPantallas->addWidget(menuJuego);

    mostrarMenuPrincipal();
    connect(menuPrincipal, SIGNAL(jugarClicked()), this, SLOT(mostrarMenuPartida()));
    connect(menuPrincipal, SIGNAL(cargarPartidaClicked()), this, SLOT(cargarPartida()));
    connect(menuPrincipal, SIGNAL(creditosClicked()), this, SLOT(mostrarCreditos()));

    // Señales del MenuPartida
    connect(menuPartida, SIGNAL(comenzarPartida(int, std::vector<std::string>, int, bool, bool)), this,
            SLOT(iniciarNuevaPartida(int, std::vector<std::string>, int, bool, bool)));
    connect(menuPartida, SIGNAL(cancelarClicked()), this, SLOT(mostrarMenuPrincipal()));

    // Señales del MenuJuego
    connect(menuJuego, SIGNAL(menuPrincipalClicked()), this, SLOT(mostrarMenuPrincipal()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (juego) delete juego;
    delete menuPrincipal;
    delete menuPartida;
    delete menuJuego;
}

void MainWindow::mostrarMenuPrincipal(){
    stackPantallas->setCurrentWidget(menuPrincipal);
}

void MainWindow::mostrarMenuPartida(){
    stackPantallas->setCurrentWidget(menuPartida);
}

void MainWindow::mostrarMenuJuego(){
    if (juego){
        menuJuego->crearPartida(juego);
        stackPantallas->setCurrentWidget(menuJuego);
    } else{
        QMessageBox::warning(this, "Error", "No hay partida cargada.");
        mostrarMenuPrincipal();
    }
}

void MainWindow::iniciarNuevaPartida(int numJugadores, std::vector<std::string> nombres, int tamTablero, bool personalizado, bool dosDados){
    if (juego){
        delete juego;
        juego = nullptr;
    }
    juego = new JuegoOCA(numJugadores, nombres, tamTablero, personalizado, dosDados);
    juego->iniciarJuego();
    mostrarMenuJuego();
}

void MainWindow::cargarPartida(){
    if (!juego){
        std::vector<std::string> auxNombres ={"Jugador 1", "Jugador 2"};
        juego = new JuegoOCA(2, auxNombres, 63, false, false);
    }

    std::string archivo = "partida.dat";
    if (juego->cargarPartida(archivo)){
        mostrarMenuJuego();
        QMessageBox::information(this, "Partida Cargada", "La partida se ha cargado correctamente.");
    } else{
        QMessageBox::warning(this, "Error", "No se pudo cargar la partida.");
        if (juego){
            delete juego;
            juego = nullptr;
        }
        mostrarMenuPrincipal();
    }
}

void MainWindow::mostrarCreditos(){
    QMessageBox::about(this, "Créditos",
                       "Juego de la Oca\n\n"
                       "Versión 1.0\n\n"
                       "Desarrollado por: Leonetti Franco y Gallardo Octavio\n\n"
                       "Proyecto de Programación Orientada a Objetos\n");
}
