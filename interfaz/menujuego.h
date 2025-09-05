#ifndef MENUJUEGO_H
#define MENUJUEGO_H

#include <QWidget>

namespace Ui {
class MenuJuego;
}

class MenuJuego : public QWidget
{
    Q_OBJECT

public:
    explicit MenuJuego(QWidget *parent = nullptr);
    ~MenuJuego();

private:
    Ui::MenuJuego *ui;
};

#endif // MENUJUEGO_H
