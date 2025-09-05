#ifndef CASILLALABERINTO_H
#define CASILLALABERINTO_H

#include "casilla.h"

class CasillaLaberinto : public Casilla
{
public:
    explicit CasillaLaberinto(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLALABERINTO_H
