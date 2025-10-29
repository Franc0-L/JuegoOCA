#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "casilla.h"

class CasillaNormal : public Casilla
{
public:
    CasillaNormal(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
    std::string getTipo () const override;
    std::string getColor() const override;
};

#endif // CASILLANORMAL_H
