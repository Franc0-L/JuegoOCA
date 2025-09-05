#include "casillapuente.h"

CasillaPuente::CasillaPuente(int numero) : Casilla(numero) {}

bool CasillaPuente::ejecutarEfecto(Jugador &jugador){
    jugador.setPosicion(12);
    return false;
}
