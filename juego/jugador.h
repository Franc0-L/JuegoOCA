#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <QColor>
#include <QDataStream>

class Jugador
{
private:
    std::string nombre;
    QColor color;
    int posicion;
    int turnosPenalizacion;
    bool enPozo;
public:
    explicit Jugador(const std::string& nombre, const QColor& color);

    std::string getNombre() const;
    QColor getColor() const;
    int getPosicion() const;
    int getTurnosPenalizacion() const;
    bool estaEnPozo() const;

    void setPosicion(int nuevaPosicion);
    void setTurnosPenalizacion(int turnos);
    void setEnPozo(bool enPozo);

    void mover(int desplazamiento);
    void actualizarTurno();

    friend QDataStream& operator<<(QDataStream& salida, const Jugador& jugador);
    friend QDataStream& operator>>(QDataStream& entrada, Jugador& jugador);
};

#endif // JUGADOR_H
