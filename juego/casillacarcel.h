#ifndef CASILLACARCEL_H
#define CASILLACARCEL_H

#include "casilla.h"

class CasillaCarcel : public Casilla
{
public:
    CasillaCarcel(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
};

#endif // CASILLACARCEL_H
