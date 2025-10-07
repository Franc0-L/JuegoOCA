#ifndef MENUCONFIGURACION_H
#define MENUCONFIGURACION_H

#include <QWidget>

namespace Ui {
class MenuConfiguracion;
}

class MenuConfiguracion : public QWidget
{
    Q_OBJECT

public:
    explicit MenuConfiguracion(QWidget *parent = nullptr);
    ~MenuConfiguracion();
signals:
    void volverClicked();
    void configuracionGuardada(int volGeneral, int volSonido, int VolMusica);
private slots:
    void onGuardarClicked();
    void onVolGeneral(int valor);
    void onVolSonido(int valor);
    void onVolMusica(int valor);
private:
    Ui::MenuConfiguracion *ui;
};

#endif // MENUCONFIGURACION_H
