#ifndef MODULOCOMFOGO_HPP
#define MODULOCOMFOGO_HPP

#include "Modulo.hpp"
using namespace std;

class ModuloComFogo : public Modulo
{
public:
    ModuloComFogo(char tipo) : Modulo(tipo) {}
    bool podeAcessar() override { return false; }
};

#endif
