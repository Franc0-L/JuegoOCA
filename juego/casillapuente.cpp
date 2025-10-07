#include "casillapuente.h"

CasillaPuente::CasillaPuente(int numero, int destino) : Casilla(numero), destino(destino) {}

ResultadoCasilla CasillaPuente::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevaPosicion = destino;
    r.descripcion = "Puente: vas a la casilla " + std::to_string(destino);

    return r;
}
