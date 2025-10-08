#include "casillacarcel.h"

CasillaCarcel::CasillaCarcel(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaCarcel::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevoEstado = Jugador::EN_CARCEL;
    r.turnos = 2;
    r.descripcion = "Carcel: pierdes 2 turnos";

    return r;
}

std::string CasillaCarcel::getTipo() const{
    return "Carcel";
}
