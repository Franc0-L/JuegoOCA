#ifndef MENUJUEGO_H
#define MENUJUEGO_H

#include <QWidget>

namespace Ui {
class MenuJuego;
}

class JuegoOCA;

class MenuJuego : public QWidget
{
    Q_OBJECT

public:
    explicit MenuJuego(QWidget *parent = nullptr);
    ~MenuJuego();

    void crearPartida(JuegoOCA* juego);
signals:
    void menuPrincipalClicked();
private slots:
    void onDadoLanzado();
    void onGuardarPartida();
    void onCargarPartida();
    void actualizarInterfaz();
private:
    Ui::MenuJuego *ui;
    JuegoOCA* juego;

    void actualizarInfoJugador();

    void actualizarTablero();
    void limpiarTablero();
    void crearCasilla(int numero, int fila, int columna);
    QString obtenerInfoJugadoresEnCasilla(int numeroCasilla);

    void actualizarHistorial();
    void agregarAlHistorial(const QString& mensaje);
};

#endif // MENUJUEGO_H
