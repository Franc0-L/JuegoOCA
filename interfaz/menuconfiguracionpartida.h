#ifndef MENUCONFIGURACIONPARTIDA_H
#define MENUCONFIGURACIONPARTIDA_H

#include <QWidget>

namespace Ui {
class MenuConfiguracionPartida;
}

class MenuConfiguracionPartida : public QWidget
{
    Q_OBJECT

public:
    explicit MenuConfiguracionPartida(QWidget *parent = nullptr);
    ~MenuConfiguracionPartida();

private:
    Ui::MenuConfiguracionPartida *ui;
};

#endif // MENUCONFIGURACIONPARTIDA_H
