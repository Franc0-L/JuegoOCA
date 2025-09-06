#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "menuprincipal.h"
#include "menuconfiguracionpartida.h"
#include "menuconfiguracion.h"
#include "menujuego.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void mostrarMenuPrincipal();
    void mostrarConfiguracionPartida();
    void mostrarConfiguracion();
    void mostrarJuego();
private:
    Ui::MainWindow *ui;

    QStackedWidget* stackedWidget;
    MenuPrincipal* menuPrincipal;
    MenuConfiguracionPartida* menuConfiguracionPartida;
    MenuConfiguracion* menuConfiguracion;
    MenuJuego* menuJuego;
};
#endif // MAINWINDOW_H
