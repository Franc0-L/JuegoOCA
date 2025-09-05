#ifndef GESTORPARTIDAS_H
#define GESTORPARTIDAS_H

#include <QString>
#include <vector>
#include "juegooca.h"

class GestorPartidas
{
public:
    static bool guardarPartida(const QString& nombreArchivo, const JuegoOCA& juego);
    static bool cargarPartida(const QString& nombreArchivo, JuegoOCA& juego);

    static std::vector<QString> listarPartidas();
};

#endif // GESTORPARTIDAS_H
