#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>

namespace Ui {
class MenuPrincipal;
}

class MenuPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();
signals:
    void jugarClicked();
    void configuracionClicked();
    void cargarPartidaClicked();
private:
    Ui::MenuPrincipal *ui;
};

#endif // MENUPRINCIPAL_H
