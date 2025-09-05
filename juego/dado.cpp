#include "dado.h"
#include <cstdlib>
#include <ctime>

Dado::Dado(int numCaras) : caras(numCaras){
    srand(time(nullptr));
}

int Dado::tirar(){
    return (rand() % caras) + 1;
}

std::vector<int> Dado::tirar(int cantidad){
    std::vector<int> resultados;
    for (int i = 0; i < cantidad; ++i){
        resultados.push_back(tirar());
    }
    return resultados;
}
