#include "casillaoca.h"

CasillaOca::CasillaOca(int numero, int destino) : Casilla(numero), destino(destino) {}

ResultadoCasilla CasillaOca::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevaPosicion = destino;
    r.volverATirar = true;
    r.descripcion = "Oca: avanzas a la casilla " + std::to_string(destino);

    return r;
}

std::string CasillaOca::getTipo() const{
    return "Oca";
}
