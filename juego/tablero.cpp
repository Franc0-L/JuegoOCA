#include "tablero.h"
#include "casillanormal.h"
#include "casillaoca.h"
#include "casillapuente.h"
#include "casillaposada.h"
#include "casillapozo.h"
#include "casillalaberinto.h"
#include "casillacarcel.h"
#include "casillacalavera.h"

Tablero::Tablero(int tamanio) : tamanio(tamanio){
    casillas.resize(tamanio + 1);
    inicializar();
}

void Tablero::inicializar(){
    for (int i = 0; i < tamanio; ++i){
        casillas[i] = std::make_unique<CasillaNormal>(i);
    }

    casillas[6] = std::make_unique<CasillaPuente>(6);
    casillas[9] = std::make_unique<CasillaOca>(9);
    casillas[18] = std::make_unique<CasillaOca>(18);
    casillas[19] = std::make_unique<CasillaPosada>(19);
    casillas[27] = std::make_unique<CasillaOca>(27);
    casillas[31] = std::make_unique<CasillaPozo>(31);
    casillas[36] = std::make_unique<CasillaOca>(36);
    casillas[42] = std::make_unique<CasillaLaberinto>(42);
    casillas[45] = std::make_unique<CasillaOca>(45);
    casillas[54] = std::make_unique<CasillaOca>(54);
    casillas[56] = std::make_unique<CasillaCarcel>(56);
    casillas[58] = std::make_unique<CasillaCalavera>(58);
}

Casilla *Tablero::getCasilla(int numero) const{
    if (numero < 1 || numero > tamanio) return nullptr;
    return casillas[numero].get();
}

int Tablero::getTamanio() const{
    return tamanio;
}
