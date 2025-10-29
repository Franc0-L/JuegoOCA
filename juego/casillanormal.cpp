#include "casillanormal.h"

CasillaNormal::CasillaNormal(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaNormal::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.descripcion = "Casilla Normal. No pasa nada";

    return r;
}

std::string CasillaNormal::getTipo() const{
    return "Normal";
}

std::string CasillaNormal::getColor() const{
    return "#b6e2a1";
}
