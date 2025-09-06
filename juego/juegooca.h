#ifndef JUEGOOCA_H
#define JUEGOOCA_H

#include <vector>
#include "jugador.h"
#include "tablero.h"
#include "dado.h"

class JuegoOCA
{
private:
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Dado dado;
    int jugadorActual;
    bool partidaTerminada;
    int jugadorEnPozo;
    bool primerTurno;
    bool usarDosDados;
public:
    JuegoOCA(int numJugadores, const std::vector<std::string>& nombres,
             const std::vector<QColor>& colores, bool usarDosDados = false);

    void siguienteTurno();
    int lanzarDado();
    std::vector<int> lanzarDados(int cantidad);
    bool moverJugador (int pasos);
    // Regla especial del primer turno con dos dados
    bool moverJugadorConDados(const std::vector<int>& resultados);

    bool partidaFinalizada() const;
    int getJugadorActual() const;
    const std::vector<Jugador>& getJugadores() const;
    const Tablero& getTablero() const;
    bool esPrimerTurno() const;
    void setUsarDosDados(bool usar);

    friend QDataStream& operator<<(QDataStream& salida, const JuegoOCA& juego);
    friend QDataStream& operator>>(QDataStream& entrada, JuegoOCA& juego);
};

#endif // JUEGOOCA_H
