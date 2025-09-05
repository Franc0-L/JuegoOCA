#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "casilla.h"

class CasillaNormal : public Casilla
{
public:
    explicit CasillaNormal(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLANORMAL_H
