#include "casillalaberinto.h"

CasillaLaberinto::CasillaLaberinto(int numero, int destino) : Casilla(numero), destino(destino) {}

ResultadoCasilla CasillaLaberinto::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevaPosicion = destino;
    r.descripcion = "Laberinto: retrocedes a la casilla " + std::to_string(destino);

    return r;
}

std::string CasillaLaberinto::getTipo() const{
    return "Laberinto";
}
