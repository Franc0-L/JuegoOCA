#ifndef MENUCONFIGURACIONGENERAL_H
#define MENUCONFIGURACIONGENERAL_H

#include <QWidget>

namespace Ui {
class MenuConfiguracionGeneral;
}

class MenuConfiguracionGeneral : public QWidget
{
    Q_OBJECT

public:
    explicit MenuConfiguracionGeneral(QWidget *parent = nullptr);
    ~MenuConfiguracionGeneral();

private:
    Ui::MenuConfiguracionGeneral *ui;
};

#endif // MENUCONFIGURACIONGENERAL_H
