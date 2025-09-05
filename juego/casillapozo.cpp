#include "casillapozo.h"

CasillaPozo::CasillaPozo(int numero) : Casilla(numero) {}

bool CasillaPozo::ejecutarEfecto(Jugador &jugador){
    jugador.setEnPozo(true);
    return false;
}
