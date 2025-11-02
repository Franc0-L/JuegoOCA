#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "interfaz/menujuego.h"
#include "interfaz/menupartida.h"
#include "interfaz/menuprincipal.h"
#include "juego/juegooca.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    // Navegación entre pantallas
    void mostrarMenuPrincipal();
    void mostrarMenuPartida();
    void mostrarMenuJuego();
    void mostrarCreditos();
    void mostrarReglas();

    void iniciarNuevaPartida(int numJugadores, std::vector<std::string> nombres, int tamTablero, bool personalizado, bool dosDados, int semilla);
    void cargarPartida();
private:
    Ui::MainWindow* ui;
    QStackedWidget* stackPantallas;

    MenuPrincipal* menuPrincipal;
    MenuPartida* menuPartida;
    MenuJuego* menuJuego;

    JuegoOCA *juego;
};
#endif // MAINWINDOW_H
