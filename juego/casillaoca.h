#ifndef CASILLAOCA_H
#define CASILLAOCA_H

#include "casilla.h"

class CasillaOca : public Casilla
{
public:
    explicit CasillaOca(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLAOCA_H
