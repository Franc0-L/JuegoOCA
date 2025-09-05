#ifndef CASILLAPUENTE_H
#define CASILLAPUENTE_H

#include "casilla.h"

class CasillaPuente : public Casilla
{
public:
    explicit CasillaPuente(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLAPUENTE_H
