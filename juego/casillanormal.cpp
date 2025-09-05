#include "casillanormal.h"

CasillaNormal::CasillaNormal(int numero) : Casilla(numero) {}

bool CasillaNormal::ejecutarEfecto(Jugador& jugador){
    return false; // No se aplica ningun efecto
}
