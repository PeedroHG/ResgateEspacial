#ifndef MODULOVAZIO_HPP
#define MODULOVAZIO_HPP

#include "Modulo.hpp"

class ModuloVazio : public Modulo
{
public:
    ModuloVazio(char tipo) : Modulo(tipo) {}
    bool podeAcessar() override { return true; }
};

#endif
