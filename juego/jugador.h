#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador
{
public:
    enum Estado{
        NORMAL, EN_POZO, EN_CARCEL, EN_POSADA
    };

    Jugador(const std::string &nombre, int id);

    std::string getNombre() const;
    int getId() const;
    int getPosicion() const;
    void setPosicion(int nuevaPosicion);

    Estado getEstado() const;
    void setEstado(Estado nuevoEstado, int turnos = 0);

    int getTurnosEstado() const;
    void actualizarEstado();
    int getPosicionPenalizado() const;
    void setPosicionPenalizado(int posicion);
    bool puedeMoverse() const;
private:
    std::string nombre;
    int id;
    int posicion;
    Estado estado;
    int turnosEstado;
    int posicionPenalizado;
};

#endif // JUGADOR_H
