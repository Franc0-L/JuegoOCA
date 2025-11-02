#ifndef MENUPARTIDA_H
#define MENUPARTIDA_H

#include <QWidget>
#include <vector>
#include <string>

namespace Ui {
class MenuPartida;
}

class MenuPartida : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPartida(QWidget *parent = nullptr);
    ~MenuPartida();
signals:
    void comenzarPartida(int numJugadores, std::vector<std::string> nombres, int tamTablero,
                         bool personalizado, bool dosDados, int semilla = 0);
    void cancelarClicked();
private slots:
    void onNumJugadores();
    void onComenzarClicked();
    void onCancelarClicked();
private:
    Ui::MenuPartida *ui;

    void actualizarInfoJugadores();
};

#endif // MENUPARTIDA_H
