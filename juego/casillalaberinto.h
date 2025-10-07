#ifndef CASILLALABERINTO_H
#define CASILLALABERINTO_H

#include "casilla.h"

class CasillaLaberinto : public Casilla
{
public:
    CasillaLaberinto(int numero, int destino);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
private:
    int destino;
};

#endif // CASILLALABERINTO_H
