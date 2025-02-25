#ifndef MODULOCOMASTRONAUTA_HPP
#define MODULOCOMASTRONAUTA_HPP
#include "Modulo.hpp"
using namespace std;

class ModuloComAstronauta : public Modulo
{
public:
    ModuloComAstronauta(char tipo) : Modulo(tipo) {}
    bool podeAcessar() override { return true; }
};

#endif
