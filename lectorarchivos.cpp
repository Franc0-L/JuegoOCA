#include "lectorarchivos.h"

vector<string> LectorArchivos::leerConfiguracion(const string &ruta){
    vector<string> lineas;

    ifstream archivo(ruta);
    if (archivo.is_open()){
        string linea;
        while (getline(archivo, linea)){
            lineas.push_back(linea);
        }
        archivo.close();
    }

    return lineas;
}

bool LectorArchivos::guardarConfiguracion(const string &ruta, const vector<string> &config){
    ofstream archivo(ruta);
    if (archivo.is_open()){
        for (const auto& linea : config){
            archivo<< linea<< endl;
        }
        archivo.close();
        return true;
    }
    return false;
}
