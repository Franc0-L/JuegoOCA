#include "casillaoca.h"

CasillaOca::CasillaOca(int numero) : Casilla(numero) {}

bool CasillaOca::ejecutarEfecto(Jugador& jugador){
    int posicionesOca[] = {9, 18, 27, 36, 45, 54, 63};
    int siguienteOca = 0;

    for (int i = 0; i < 7; ++i){
        if (posicionesOca[i] > numero){
            siguienteOca = posicionesOca[i];
            break;
        }
    }

    if (siguienteOca == 0){
        siguienteOca = 63;
    }

    jugador.setPosicion(siguienteOca);
    return true;
}
