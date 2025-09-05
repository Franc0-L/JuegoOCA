#ifndef CASILLA_H
#define CASILLA_H

#include "jugador.h"

class Casilla
{
protected:
    int numero;
public:
    explicit Casilla(int numero);
    virtual ~Casilla() = default;

    virtual bool ejecutarEfecto(Jugador& jugador) = 0;
    int getNumero() const;
};

#endif // CASILLA_H
