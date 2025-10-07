#ifndef CASILLAPOSADA_H
#define CASILLAPOSADA_H

#include "casilla.h"

class CasillaPosada : public Casilla
{
public:
    CasillaPosada(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
};

#endif // CASILLAPOSADA_H
