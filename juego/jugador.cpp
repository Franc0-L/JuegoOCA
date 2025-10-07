#include "jugador.h"

Jugador::Jugador(const std::string &nombre, int id)
    : nombre(nombre), id(id), posicion(1), estado(NORMAL), turnosEstado(0), posicionPenalizado(0) {}

std::string Jugador::getNombre() const{
    return nombre;
}

int Jugador::getId() const{
    return id;
}

int Jugador::getPosicion() const{
    return posicion;
}

void Jugador::setPosicion(int nuevaPosicion){
    posicion = nuevaPosicion;
}

Jugador::Estado Jugador::getEstado() const{
    return estado;
}

void Jugador::setEstado(Estado nuevoEstado, int turnos){
    estado = nuevoEstado;
    if (nuevoEstado == EN_CARCEL || nuevoEstado == EN_POSADA){
        turnosEstado = turnos;
    } else{
        turnosEstado = 0;
    }
}

int Jugador::getTurnosEstado() const{
    return turnosEstado;
}

void Jugador::actualizarEstado(){
    if (estado == EN_CARCEL || estado == EN_POSADA){
        if (turnosEstado > 0){
            --turnosEstado;
        }
        if (turnosEstado <= 0){
            estado = NORMAL;
            turnosEstado = 0;
        }
    }
}

int Jugador::getPosicionPenalizado() const{
    return posicionPenalizado;
}

void Jugador::setPosicionPenalizado(int posicion){
    posicionPenalizado = posicion;
}

bool Jugador::puedeMoverse() const{
    return estado == NORMAL;
}
