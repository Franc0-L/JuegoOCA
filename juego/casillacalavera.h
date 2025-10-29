#ifndef CASILLACALAVERA_H
#define CASILLACALAVERA_H

#include "casilla.h"

class CasillaCalavera : public Casilla
{
public:
    CasillaCalavera(int numero);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
    std::string getTipo () const override;
    std::string getColor() const override;
};

#endif // CASILLACALAVERA_H
