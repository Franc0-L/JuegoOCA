#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "casilla.h"

class Tablero
{
public:
    Tablero(int tamanio = 63, bool personalizado = false, int semilla = 0);
    ~Tablero();

    Casilla* getCasilla(int numero) const;
    int getSemilla() const;
    bool esPersonalizado() const;

    int getTamanio() const;
    void setTamanio(int nuevoTamanio, bool esPersonalizado, int nuevaSemilla = 0);
private:
    std::vector<Casilla*> casillas;
    int tamanio;
    bool personalizado;
    int semilla;

    void limpiarCasillas();
    void inicializarTablero(); // Tablero clasico
    void iniTableroPersonalizado();
    void armarCasillasAleatorias();
};

#endif // TABLERO_H
