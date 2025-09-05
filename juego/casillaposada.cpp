#include "casillaposada.h"

CasillaPosada::CasillaPosada(int numero) : Casilla(numero) {}

bool CasillaPosada::ejecutarEfecto(Jugador& jugador){
    jugador.setTurnosPenalizacion(1);
    return false;
}
