#include "casillaposada.h"

CasillaPosada::CasillaPosada(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaPosada::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.nuevoEstado = Jugador::EN_POSADA;
    r.turnos = 1;
    r.descripcion = "Posada: pierdes 1 turno";

    return r;
}
