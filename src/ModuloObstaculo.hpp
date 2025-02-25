#ifndef MODULOOBSTACULO_HPP
#define MODULOOBSTACULO_HPP

#include "Modulo.hpp"

class ModuloObstaculo : public Modulo
{
public:
    ModuloObstaculo(char tipo) : Modulo(tipo) {}
    bool podeAcessar() override { return false; }
};

#endif
