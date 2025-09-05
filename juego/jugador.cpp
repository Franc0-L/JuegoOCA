#include "jugador.h"

Jugador::Jugador(const std::string &nombre, const QColor &color)
    : nombre(nombre), color(color), posicion(0), turnosPenalizacion(0), enPozo(false) {}

std::string Jugador::getNombre() const{
    return nombre;
}

QColor Jugador::getColor() const{
    return color;
}

int Jugador::getPosicion() const{
    return posicion;
}

int Jugador::getTurnosPenalizacion() const{
    return turnosPenalizacion;
}

bool Jugador::estaEnPozo() const{
    return enPozo;
}

void Jugador::setPosicion(int nuevaPosicion){
    posicion = nuevaPosicion;
}

void Jugador::setTurnosPenalizacion(int turnos){
    turnosPenalizacion = turnos;
}

void Jugador::setEnPozo(bool enPozo){
    this->enPozo = enPozo;
}

void Jugador::mover(int desplazamiento){
    posicion += desplazamiento;
}

void Jugador::actualizarTurno(){
    if (turnosPenalizacion > 0){
        turnosPenalizacion--;
    }
}

QDataStream& operator<<(QDataStream& salida, const Jugador& jugador){
    salida << QString::fromStdString(jugador.nombre)
        << jugador.color
        << jugador.posicion
        << jugador.turnosPenalizacion
        << jugador.enPozo;

    return salida;
}

QDataStream& operator>>(QDataStream& entrada, Jugador& jugador) {
    QString nombre;
    QColor color;
    int posicion, turnosPenalizacion;
    bool enPozo;

    entrada>> nombre>> color>> posicion>> turnosPenalizacion>> enPozo;
    jugador = Jugador(nombre.toStdString(), color);
    jugador.setPosicion(posicion);
    jugador.setTurnosPenalizacion(turnosPenalizacion);
    jugador.setEnPozo(enPozo);

    return entrada;
}
