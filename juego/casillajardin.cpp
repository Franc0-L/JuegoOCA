#include "casillajardin.h"

CasillaJardin::CasillaJardin(int numero) : Casilla(numero) {}

ResultadoCasilla CasillaJardin::aplicarEfecto(Jugador &jugador){
    ResultadoCasilla r;
    r.descripcion = "Jardin: eres el ganador. Felicidades!";

    return r;
}
