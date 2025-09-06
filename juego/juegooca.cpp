#include "juegooca.h"

JuegoOCA::JuegoOCA(int numJugadores, const std::vector<std::string> &nombres,
                   const std::vector<QColor> &colores, bool usarDosDados)
    : tablero(63), jugadorActual(0), partidaTerminada(false), jugadorEnPozo(-1),
    primerTurno(true), usarDosDados(usarDosDados){

    for (int i = 0; i < numJugadores; ++i){
        jugadores.emplace_back(nombres[i], colores[i]);
    }
}

void JuegoOCA::siguienteTurno(){
    for (auto& jugador : jugadores){
        jugador.actualizarTurno();
    }

    do{
        jugadorActual = (jugadorActual + 1) % jugadores.size();
    } while (jugadores[jugadorActual].getTurnosPenalizacion() > 0 || jugadores[jugadorActual].estaEnPozo());
    primerTurno = false;
}

int JuegoOCA::lanzarDado(){
    return dado.tirar();
}

std::vector<int> JuegoOCA::lanzarDados(int cantidad){
    return dado.tirar(cantidad);
}

bool JuegoOCA::moverJugador(int pasos){
    Jugador& jugador = jugadores[jugadorActual];
    int nuevaPos = jugador.getPosicion() + pasos;

    // Verificar ganador
    if (nuevaPos == tablero.getTamanio()){
        jugador.setPosicion(nuevaPos);
        partidaTerminada = true;
        return false;
    }

    // Rebote
    if (nuevaPos > tablero.getTamanio()){
        nuevaPos = tablero.getTamanio() - (nuevaPos - tablero.getTamanio());
    }

    jugador.setPosicion(nuevaPos);

    // Logica de Casilla Pozo
    if (nuevaPos == 31){
        if (jugadorEnPozo != -1){
            jugadores[jugadorEnPozo].setEnPozo(false);
            jugadorEnPozo = -1;
        }
        jugador.setEnPozo(true);
        jugadorEnPozo = jugadorActual;
    }

    // Aplicamos efecto de la casilla en la que cae el jugador
    Casilla* casilla = tablero.getCasilla(nuevaPos);
    if (casilla){
        return casilla->ejecutarEfecto(jugador);
    }

    return false;
}

bool JuegoOCA::moverJugadorConDados(const std::vector<int> &resultados){
    int suma = 0;
    for (int resultado : resultados){
        suma += resultado;
    }

    // Regla especial del primer turno con dos dados
    if (primerTurno && usarDosDados && resultados.size() == 2 && suma == 9){
        std::vector<int> resultadosSort = resultados;
        std::sort(resultadosSort.begin(), resultadosSort.end());

        if (resultadosSort[0] == 3 && resultadosSort[1] == 6){
            jugadores[jugadorActual].setPosicion(36);
        } else if (resultadosSort[0] == 4 && resultadosSort[1] == 5){
            jugadores[jugadorActual].setPosicion(54);
        } else{
            jugadores[jugadorActual].setPosicion(suma);
        }

        primerTurno = false;
        return true;
    }

    // Regla de un dado a partir de la casilla 60
    if (jugadores[jugadorActual].getPosicion() >= 60 && resultados.size() > 1){
        suma = resultados[0]; // Usar solo el primer dado
    }

    return moverJugador(suma);
}

bool JuegoOCA::partidaFinalizada() const{
    return partidaTerminada;
}

int JuegoOCA::getJugadorActual() const{
    return jugadorActual;
}

const std::vector<Jugador> &JuegoOCA::getJugadores() const{
    return jugadores;
}

const Tablero &JuegoOCA::getTablero() const{
    return tablero;
}

bool JuegoOCA::esPrimerTurno() const{
    return primerTurno;
}

void JuegoOCA::setUsarDosDados(bool usar){
    usarDosDados = usar;
}

QDataStream& operator<<(QDataStream& salida, const JuegoOCA& juego){
    salida<< juego.jugadores.size();
    for (const auto& jugador : juego.jugadores){
        salida << QString::fromStdString(jugador.getNombre())
               << jugador.getColor()
               << jugador.getPosicion()
               << jugador.getTurnosPenalizacion()
               << jugador.estaEnPozo();
    }

    salida << juego.jugadorActual<< juego.partidaTerminada<< juego.jugadorEnPozo
           << juego.primerTurno<< juego.usarDosDados;

    return salida;
}

QDataStream& operator>>(QDataStream& entrada, JuegoOCA& juego){
    int numJugadores;
    entrada>> numJugadores;
    juego.jugadores.clear();

    for (int i = 0; i < numJugadores; ++i){
        QString nombre;
        QColor color;
        int posicion, turnosPenalizacion;
        bool enPozo;

        entrada>> nombre>> color>> posicion>> turnosPenalizacion>> enPozo;
        juego.jugadores.emplace_back(nombre.toStdString(), color);
        juego.jugadores.back().setPosicion(posicion);
        juego.jugadores.back().setTurnosPenalizacion(turnosPenalizacion);
        juego.jugadores.back().setEnPozo(enPozo);
    }

    entrada >> juego.jugadorActual>> juego.partidaTerminada>> juego.jugadorEnPozo
        >> juego.primerTurno>> juego.usarDosDados;

    return entrada;
}
