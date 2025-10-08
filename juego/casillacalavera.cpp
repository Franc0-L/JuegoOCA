#include "casillacalavera.h"

CasillaCalavera::CasillaCalavera(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaCalavera::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevaPosicion = 1;
    r.descripcion = "Calavera: vuelves al inicio";

    return r;
}

std::string CasillaCalavera::getTipo() const{
    return "Calavera";
}
