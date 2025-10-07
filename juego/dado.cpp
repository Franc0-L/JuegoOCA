#include "dado.h"
#include <cstdlib>
#include <ctime>

Dado::Dado(int caras) : caras(caras){
    if (caras <= 0) this->caras = 6;
    srand(time(nullptr));
}

int Dado::tirar(){
    return (rand() % caras) + 1;
}

void Dado::tiradaDoble(int &resultado1, int &resultado2){
    resultado1 = tirar();
    resultado2 = tirar();
}
