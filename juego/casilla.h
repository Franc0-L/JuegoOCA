#ifndef CASILLA_H
#define CASILLA_H

#include <string>
#include "jugador.h"

struct ResultadoCasilla{
    int nuevaPosicion = -1; // No hay cambios de posicion
    Jugador::Estado nuevoEstado = Jugador::NORMAL; // Para casos donde el estado cambia
    int turnos = 0; // Para efectos relacionado a turnos
    bool volverATirar = false; // Para efectos relacionado a tiradas
    std::string descripcion;
};

class Casilla
{
public:
    Casilla(int numero);
    virtual ~Casilla() = default;

    virtual ResultadoCasilla aplicarEfecto(Jugador &jugador) = 0;
    int getNumero() const;
protected:
    int numero;
};

#endif // CASILLA_H
