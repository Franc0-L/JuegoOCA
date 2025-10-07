#include "juegooca.h"
#include "casillapozo.h"
#include <fstream>

JuegoOCA::JuegoOCA(int numJugadores, std::vector<std::string> &nombres, int tamTablero, bool tableroPersonalizado, bool dosDados)
    : tablero(tamTablero, tableroPersonalizado), dado(), jugadorActual(0), juegoTerminado(false), usarDosDados(dosDados),
    tableroPersonalizado(tableroPersonalizado),  turno(1){

    for (int i = 0; i < numJugadores; ++i){
        jugadores.emplace_back(nombres[i], i + 1);
    }
}

void JuegoOCA::iniciarJuego(){
    juegoTerminado = false;
    jugadorActual = 0;
    turno = 1;

    for (auto &jugador : jugadores){
        jugador.setPosicion(1);
        jugador.setEstado(Jugador::NORMAL);
        jugador.setPosicionPenalizado(0);
    }
}

void JuegoOCA::siguienteTurno(){
    if (juegoTerminado) return;

    Jugador &jugador = jugadores[jugadorActual];
    auto estado = jugador.getEstado();

    if (estado == Jugador::EN_CARCEL || estado == Jugador::EN_POSADA){
        jugador.actualizarEstado();
        if (jugador.getTurnosEstado() > 0){
            jugadorActual++;
            if (jugadorActual >= jugadores.size()){
                jugadorActual = 0;
                turno++;
            }
            return;
        }
    }
    if (estado == Jugador::EN_POZO){
        jugadorActual++;
        if (jugadorActual >= jugadores.size()){
            jugadorActual = 0;
            turno++;
        }
        return;
    }

    lanzarDados();
}

void JuegoOCA::lanzarDados(){
    if (juegoTerminado) return;

    int pasos = 0;

    if (usarDosDados){
        int d1 = 0, d2 = 0;
        dado.tiradaDoble(d1, d2);
        pasos = d1 + d2;
        // Regla especial para tiradas con doble dado
        if ((d1 + 1 == d2) || (d2 + 1 == d1)){
            pasos += 1;
        }
        else if (d1 == d2){
            pasos += 2;
        }
    } else{
        pasos = dado.tirar();
    }

    moverJugador(pasos);
}

void JuegoOCA::moverJugador(int pasos){
    if (juegoTerminado) return;

    Jugador &jugador = jugadores[jugadorActual];
    int nuevaPosicion = jugador.getPosicion() + pasos;
    int tamanio = tablero.getTamanio();

    // Rebote si supera el final
    if (nuevaPosicion > tamanio){
        nuevaPosicion = tamanio - (nuevaPosicion - tamanio);
        if (nuevaPosicion < 1) nuevaPosicion = 1;
    }

    jugador.setPosicion(nuevaPosicion);
    // Verificar si gano
    if (nuevaPosicion == tamanio){
        juegoTerminado = true;
        return;
    }

    Casilla* casilla = tablero.getCasilla(nuevaPosicion);
    if (casilla){
        ResultadoCasilla resultado = casilla->aplicarEfecto(jugador);
        aplicarEfectoCasilla(resultado, jugador, nuevaPosicion);
    } else{
        jugadorActual++;
        if (jugadorActual >= jugadores.size()){
            jugadorActual = 0;
            turno++;
        }
    }
}


void JuegoOCA::aplicarEfectoCasilla(ResultadoCasilla &resultado, Jugador &jugador, int casillaActual){
    int casillaFinal = casillaActual;

    // Aplicar nueva posicion
    if (resultado.nuevaPosicion != -1){
        jugador.setPosicion(resultado.nuevaPosicion);
        casillaFinal = resultado.nuevaPosicion;
        if (resultado.nuevaPosicion == tablero.getTamanio()){
            juegoTerminado = true;
            return;
        }
    }

    // Aplicar nuevo estado (Si corresponde)
    if (resultado.nuevoEstado != Jugador::NORMAL){
        jugador.setEstado(resultado.nuevoEstado, resultado.turnos);
        if (resultado.nuevoEstado == Jugador::EN_POZO){
            jugador.setPosicionPenalizado(casillaFinal);
        } else{
            jugador.setPosicionPenalizado(0);
        }
    }

    // Logica para la casilla Pozo
    Casilla* cas = tablero.getCasilla(casillaFinal);
    if (dynamic_cast<CasillaPozo*>(cas) != nullptr){
        for (auto &otroJugador : jugadores){
            if (otroJugador.getId() != jugador.getId() &&
                otroJugador.getEstado() == Jugador::EN_POZO &&
                otroJugador.getPosicionPenalizado() == casillaFinal){
                otroJugador.setEstado(Jugador::NORMAL);
                otroJugador.setPosicionPenalizado(0);
            }
        }
    }

    // Manejo de turnos extra
    if (resultado.volverATirar){
        return;
    } else{
        jugadorActual++;
        if (jugadorActual >= jugadores.size()){
            jugadorActual = 0;
            turno++;
        }
    }
}

bool JuegoOCA::getJuegoTerminado() const{
    return juegoTerminado;
}

int JuegoOCA::getJugadorActual() const{
    return jugadorActual;
}

Jugador &JuegoOCA::getJugadorPorIndice(int indice){
    return jugadores.at(indice);
}

const Tablero &JuegoOCA::getTablero() const{
    return tablero;
}

int JuegoOCA::getTurno() const{
    return turno;
}

void JuegoOCA::setTableroPersonalizado(bool personalizado){
    this->tableroPersonalizado = personalizado;
    int tamanioActual = tablero.getTamanio();
    tablero = Tablero(tamanioActual, personalizado);
}

void JuegoOCA::setTamanioTablero(int tamanio){
    tablero.setTamanio(tamanio);
}

void JuegoOCA::guardarPartida(std::string &archivo){
    std::ofstream guardar(archivo, std::ios::binary);
    if (!guardar.is_open()) return;

    guardar.write((char*)&jugadorActual, sizeof(jugadorActual));
    guardar.write((char*)&juegoTerminado, sizeof(juegoTerminado));
    guardar.write((char*)&usarDosDados, sizeof(usarDosDados));
    guardar.write((char*)&tableroPersonalizado, sizeof(tableroPersonalizado));
    guardar.write((char*)&turno, sizeof(turno));

    int tamanioTablero = tablero.getTamanio();
    guardar.write((char*)&tamanioTablero, sizeof(tamanioTablero));
    int numJugadores = jugadores.size();
    guardar.write((char*)&numJugadores, sizeof(numJugadores));

    for (auto &j : jugadores){
        int tamNombre = j.getNombre().size();
        guardar.write((char*)&tamNombre, sizeof(tamNombre));
        guardar.write(j.getNombre().c_str(), tamNombre);
        int posicion = j.getPosicion();
        guardar.write((char*)&posicion, sizeof(posicion));
        int estado = j.getEstado();
        guardar.write((char*)&estado, sizeof(estado));
        int turnosEstado = j.getTurnosEstado();
        guardar.write((char*)&turnosEstado, sizeof(turnosEstado));
        int posicionPenalizado = j.getPosicionPenalizado();
        guardar.write((char*)&posicionPenalizado, sizeof(posicionPenalizado));
    }

    guardar.close();
}

bool JuegoOCA::cargarPartida(std::string &archivo){
    std::ifstream cargar(archivo, std::ios::binary);
    if (!cargar.is_open()) return false;

    cargar.read((char*)&jugadorActual, sizeof(jugadorActual));
    cargar.read((char*)&juegoTerminado, sizeof(juegoTerminado));
    cargar.read((char*)&usarDosDados, sizeof(usarDosDados));
    cargar.read((char*)&tableroPersonalizado, sizeof(tableroPersonalizado));
    cargar.read((char*)&turno, sizeof(turno));

    int tamanioTablero;
    cargar.read((char*)&tamanioTablero, sizeof(tamanioTablero));
    int numJugadores;
    cargar.read((char*)&numJugadores, sizeof(numJugadores));

    jugadores.clear();
    for (int i = 0; i < numJugadores; ++i){
        int tamNombre;
        cargar.read((char*)&tamNombre, sizeof(tamNombre));
        std::string nombre;
        nombre.resize(tamNombre);
        cargar.read(&nombre[0], tamNombre);

        jugadores.emplace_back(nombre, (i + 1));
        int posicion;
        cargar.read((char*)&posicion, sizeof(posicion));
        jugadores[i].setPosicion(posicion);

        int estado;
        cargar.read((char*)&estado, sizeof(estado));

        int turnosEstado;
        cargar.read((char*)&turnosEstado, sizeof(turnosEstado));

        int posicionPenalizado;
        cargar.read((char*)&posicionPenalizado, sizeof(posicionPenalizado));
        jugadores[i].setPosicionPenalizado(posicionPenalizado);
        jugadores[i].setEstado(Jugador::Estado(estado), turnosEstado);
    }

    tablero.setTamanio(tamanioTablero);

    cargar.close();
    return true;
}
