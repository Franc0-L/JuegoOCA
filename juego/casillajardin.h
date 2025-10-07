#ifndef CASILLAJARDIN_H
#define CASILLAJARDIN_H

#include "casilla.h"

class CasillaJardin : public Casilla
{
public:
    CasillaJardin(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
};

#endif // CASILLAJARDIN_H
