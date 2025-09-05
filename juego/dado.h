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
};

#endif // DADO_H
