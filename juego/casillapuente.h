#ifndef CASILLAPUENTE_H
#define CASILLAPUENTE_H

#include "casilla.h"

class CasillaPuente : public Casilla
{
public:
    CasillaPuente(int numero, int destino);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
    std::string getTipo () const override;
    std::string getColor() const override;
private:
    int destino;
};

#endif // CASILLAPUENTE_H
