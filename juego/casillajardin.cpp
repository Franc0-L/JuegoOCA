#include "casillajardin.h"

CasillaJardin::CasillaJardin(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaJardin::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.descripcion = "Jardin: eres el ganador. Felicidades!";

    return r;
}

std::string CasillaJardin::getTipo() const{
    return "Jardin";
}

std::string CasillaJardin::getColor() const{
    return "#8bd18b";
}
