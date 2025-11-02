#include "tablero.h"
#include "casilla.h"
#include "casillacalavera.h"
#include "casillacarcel.h"
#include "casillajardin.h"
#include "casillalaberinto.h"
#include "casillanormal.h"
#include "casillaoca.h"
#include "casillaposada.h"
#include "casillapozo.h"
#include "casillapuente.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Tablero::Tablero(int tamanio, bool personalizado, int semilla) : tamanio(tamanio), personalizado(personalizado), semilla(semilla){
    if (this->semilla == 0) this->semilla = static_cast<int>(time(nullptr));
    srand(this->semilla);

    if (personalizado){
        iniTableroPersonalizado();
    } else{
        inicializarTablero();
    }
}

Tablero::~Tablero(){
    limpiarCasillas();
}

void Tablero::limpiarCasillas(){
    for (Casilla* casilla : casillas) delete casilla;
    casillas.clear();
}

void Tablero::inicializarTablero(){
    casillas.clear();
    casillas.reserve(tamanio);
    for (int i = 0; i < tamanio; ++i){
        casillas.push_back(new CasillaNormal(i + 1));
    }
    casillas[5]  = new CasillaPuente(6, 12);
    casillas[8]  = new CasillaOca(9, 18);
    casillas[17] = new CasillaOca(18, 27);
    casillas[18] = new CasillaPosada(19);
    casillas[26] = new CasillaOca(27, 36);
    casillas[30] = new CasillaPozo(31);
    casillas[35] = new CasillaOca(36, 45);
    casillas[41] = new CasillaLaberinto(42, 30);
    casillas[44] = new CasillaOca(45, 54);
    casillas[53] = new CasillaOca(54, 63);
    casillas[55] = new CasillaCarcel(56);
    casillas[57] = new CasillaCalavera(58);
    casillas[62] = new CasillaJardin(63);
}

void Tablero::iniTableroPersonalizado(){
    casillas.clear();
    casillas.reserve(tamanio);
    for (int i = 0; i < tamanio; ++i){
        casillas.push_back(new CasillaNormal(i + 1));
    }
    armarCasillasAleatorias();
    // Ultima casilla jardin
    casillas[tamanio - 1] = new CasillaJardin(tamanio);
}

void Tablero::armarCasillasAleatorias(){
    int porcentaje = 10 + (rand() % 6); // entre un 10% y un 15% del tablero
    int cantEspeciales = tamanio * porcentaje / 100;

    for (int i = 0; i < cantEspeciales; ++i){
        int j = 1 + (rand() % (tamanio - 2)); // Rango posible
        int numero = j + 1;
        int tipo = rand() % 7; // Casillas Especiales

        delete casillas[j];

        switch (tipo){
        case 0:
            casillas[j] = new CasillaOca(numero, std::min(numero + 9, tamanio));
            break;
        case 1:
            casillas[j] = new CasillaPuente(numero, std::min(numero + 13, tamanio));
            break;
        case 2:
            casillas[j] = new CasillaPosada(numero);
            break;
        case 3:
            casillas[j] = new CasillaPozo(numero);
            break;
        case 4:
            casillas[j] = new CasillaLaberinto(numero, std::max(1, numero - 12));
            break;
        case 5:
            casillas[j] = new CasillaCarcel(numero);
            break;
        case 6:
            casillas[j] = new CasillaCalavera(numero);
            break;
        default:
            casillas[j] = new CasillaNormal(numero);
            break;
        }
    }
}

Casilla* Tablero::getCasilla(int numero) const{
    if (numero < 1 || numero > tamanio) return nullptr;
    return casillas[numero - 1];
}

int Tablero::getSemilla() const{
    return semilla;
}

bool Tablero::esPersonalizado() const{
    return personalizado;
}

int Tablero::getTamanio() const{
    return tamanio;
}

void Tablero::setTamanio(int nuevoTamanio, bool esPersonalizado, int nuevaSemilla){
    if (nuevoTamanio == tamanio && esPersonalizado == personalizado && (nuevaSemilla == 0 || nuevaSemilla == semilla)) return;

    // Actualizar propiedades
    tamanio = nuevoTamanio;
    personalizado = esPersonalizado;

    // Usar nueva semilla si se proporciona, de lo contrario mantener la actual
    if (nuevaSemilla != 0) semilla = nuevaSemilla;

    // Limpiar casillas existentes
    limpiarCasillas();

    // Reinicializar generador con la semilla
    srand(semilla);

    // Reconstruir tablero
    if (personalizado){
        iniTableroPersonalizado();
    } else{
        inicializarTablero();
    }
}
