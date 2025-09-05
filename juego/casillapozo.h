#ifndef CASILLAPOZO_H
#define CASILLAPOZO_H

#include "casilla.h"

class CasillaPozo : public Casilla
{
public:
    explicit CasillaPozo(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLAPOZO_H
