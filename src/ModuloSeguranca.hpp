#ifndef MODULOSEGURANCA_HPP
#define MODULOSEGURANCA_HPP

#include "Modulo.hpp"

class ModuloSeguranca : public Modulo
{
public:
    ModuloSeguranca(char tipo) : Modulo(tipo) {}
    bool podeAcessar() override { return true; }
};

#endif
