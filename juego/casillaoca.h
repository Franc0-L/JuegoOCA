#ifndef CASILLAOCA_H
#define CASILLAOCA_H

#include "casilla.h"

class CasillaOca : public Casilla
{
public:
    CasillaOca(int numero, int destino);

    ResultadoCasilla aplicarEfecto(Jugador &jugador) override;
    std::string getTipo () const override;
private:
    int destino;
};

#endif // CASILLAOCA_H
