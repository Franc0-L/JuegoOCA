#include "casillacalavera.h"

CasillaCalavera::CasillaCalavera(int numero) : Casilla(numero) {}

bool CasillaCalavera::ejecutarEfecto(Jugador &jugador){
    jugador.setPosicion(1);
    return false;
}
