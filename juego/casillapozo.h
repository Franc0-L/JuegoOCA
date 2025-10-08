#ifndef CASILLAPOZO_H
#define CASILLAPOZO_H

#include "casilla.h"

class CasillaPozo : public Casilla
{
public:
    CasillaPozo(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
    std::string getTipo () const override;
};

#endif // CASILLAPOZO_H
