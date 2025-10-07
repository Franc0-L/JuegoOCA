#ifndef DADO_H
#define DADO_H

class Dado
{
public:
    Dado(int caras = 6);

    int tirar();
    void tiradaDoble(int &resultado1, int &resultado2);
private:
    int caras;
};

#endif // DADO_H
