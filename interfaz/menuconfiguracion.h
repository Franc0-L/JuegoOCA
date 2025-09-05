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

private:
    Ui::MenuConfiguracion *ui;
};

#endif // MENUCONFIGURACION_H
