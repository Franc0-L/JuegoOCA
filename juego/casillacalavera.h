#ifndef CASILLACALAVERA_H
#define CASILLACALAVERA_H

#include "casilla.h"

class CasillaCalavera : public Casilla
{
public:
    explicit CasillaCalavera(int numero);

    bool ejecutarEfecto(Jugador& jugador) override;
};

#endif // CASILLACALAVERA_H
