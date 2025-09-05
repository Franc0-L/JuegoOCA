#include "casillacarcel.h"

CasillaCarcel::CasillaCarcel(int numero) : Casilla(numero) {}

bool CasillaCarcel::ejecutarEfecto(Jugador &jugador){
    jugador.setTurnosPenalizacion(2);
    return false;
}
