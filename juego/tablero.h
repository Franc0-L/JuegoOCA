#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <memory>
#include "casilla.h"

class Tablero
{
private:
    std::vector<std::unique_ptr<Casilla>> casillas;
    int tamanio;
public:
    explicit Tablero(int tamanio = 63);

    void inicializar();
    Casilla* getCasilla(int numero) const;
    int getTamanio() const;
};

#endif // TABLERO_H
