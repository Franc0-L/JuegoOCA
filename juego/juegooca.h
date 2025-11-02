#ifndef JUEGOOCA_H
#define JUEGOOCA_H

#include <vector>
#include <string>
#include "jugador.h"
#include "tablero.h"
#include "dado.h"

class JuegoOCA
{
public:
    JuegoOCA(int numJugadores, std::vector<std::string> &nombres, int tamTablero = 63,
             bool tableroPersonalizado = false, bool dosDados = false, int semillaTablero = 0);
    ~JuegoOCA() = default;

    void iniciarJuego();
    void siguienteTurno();
    void lanzarDados();
    void moverJugador(int pasos);

    bool getJuegoTerminado() const;
    int getJugadorActual() const;
    Jugador &getJugadorPorIndice(int indice);
    const Tablero &getTablero() const;
    int getTurno() const;

    void setUsarDosDados(bool usarDos);
    void setTableroPersonalizado(bool personalizado);
    void setTamanioTablero(int tamanio);

    void guardarConfiguracion(std::string &archivo);
    void guardarPartida(std::string &archivo);
    bool cargarPartida(std::string &archivo);
private:
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Dado dado;
    size_t jugadorActual;
    bool juegoTerminado;
    bool usarDosDados;
    bool tableroPersonalizado;
    int turno;

    void aplicarEfectoCasilla(ResultadoCasilla &resultado, Jugador &jugador, int casillaActual);
};

#endif // JUEGOOCA_H
