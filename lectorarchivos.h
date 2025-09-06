#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class LectorArchivos
{
public:
    static vector<string> leerConfiguracion(const string& ruta);
    static bool guardarConfiguracion(const string& ruta, const vector<string>& config);
};

#endif // LECTORARCHIVOS_H
