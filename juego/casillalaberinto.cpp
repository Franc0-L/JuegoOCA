#include "casillalaberinto.h"

CasillaLaberinto::CasillaLaberinto(int numero) : Casilla(numero) {}

bool CasillaLaberinto::ejecutarEfecto(Jugador &jugador){
    jugador.setPosicion(30);
    return false;
}
