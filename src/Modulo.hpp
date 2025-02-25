#ifndef MODULO_HPP
#define MODULO_HPP
using namespace std;

class Modulo
{
protected:
    char tipo;

public:
    Modulo(char tipo) : tipo(tipo) {}
    virtual ~Modulo() {}
    char getTipo() { return tipo; }
    void setTipo(char tipo) { this->tipo = tipo; }
    virtual bool podeAcessar() { return true; }
};

#endif
