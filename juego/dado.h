#ifndef DADO_H
#define DADO_H

#include <vector>

class Dado
{
private:
    int caras;
public:
    explicit Dado(int numCaras = 6);

    int tirar(); // Tirada aleatoria (1 a 6)
    std::vector<int> tirar(int cantidad); // Tirada aleatoria segun la cantidad de dados

    // Consigna de Regla Adicional
    std::pair<int, int> tiradaModificada(int modificador);
};

#endif // DADO_H
