#ifndef CASILLACARCEL_H
#define CASILLACARCEL_H

#include "casilla.h"

class CasillaCarcel : public Casilla
{
public:
    explicit CasillaCarcel(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLACARCEL_H
