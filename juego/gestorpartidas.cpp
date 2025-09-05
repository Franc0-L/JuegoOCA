#include "gestorpartidas.h"
#include <QDir>
#include <QCoreApplication>
#include <QDataStream>

bool GestorPartidas::guardarPartida(const QString &nombreArchivo, const JuegoOCA &juego){
    QDir dir(QCoreApplication::applicationDirPath() + "/saves");
    if (!dir.exists()){
        dir.mkpath(".");
    }

    QFile file(dir.filePath(nombreArchivo));
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }
    QDataStream salida(&file);
    salida<< juego;
    file.close();

    return true;
}

bool GestorPartidas::cargarPartida(const QString &nombreArchivo, JuegoOCA &juego){
    QDir dir(QCoreApplication::applicationDirPath() + "/saves");
    if (!dir.exists()){
        return false;
    }

    QFile file(dir.filePath(nombreArchivo));
    if (!file.open(QIODevice::ReadOnly)){
        return false;
    }
    QDataStream entrada(&file);
    entrada>> juego;
    file.close();

    return true;
}

std::vector<QString> GestorPartidas::listarPartidas(){
    std::vector<QString> partidas;
    QDir dir(QCoreApplication::applicationDirPath() + "/saves");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QStringList filtro;
    filtro<< "*.oca";
    dir.setNameFilters(filtro);

    QFileInfoList lista = dir.entryInfoList();
    for (const QFileInfo& fileinfo : lista){
        partidas.push_back(fileinfo.fileName());
    }
    return partidas;
}
