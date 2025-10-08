#include "casillapozo.h"

CasillaPozo::CasillaPozo(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaPozo::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevoEstado = Jugador::EN_POZO;
    r.turnos = 0;
    r.descripcion = "Pozo: quedas atrapado hasta que otro jugador te salve";

    return r;
}

std::string CasillaPozo::getTipo() const{
    return "Pozo";
}
