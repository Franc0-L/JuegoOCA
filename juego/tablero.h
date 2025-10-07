#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "casilla.h"

class Tablero
{
public:
    Tablero(int tamanio = 63, bool personalizado = false);
    ~Tablero() = default;

    Casilla* getCasilla(int numero) const;
    int getTamanio() const;
    void setTamanio(int nuevoTamanio);
private:
    std::vector<Casilla*> casillas;
    int tamanio;
    bool personalizado;

    void inicializarTablero(); // Tablero clasico
    void iniTableroPersonalizado();
    void armarCasillasAleatorias();
};

#endif // TABLERO_H
