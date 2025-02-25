#ifndef ASTRONAUTA_HPP
#define ASTRONAUTA_HPP
#include <string>
using namespace std;

class Astronauta
{
protected:
    string nome;
    int nivelSaude;
    bool atendimentoUrgente;
    int x;
    int y;

public:
    Astronauta(string nome, int nivelSaude, bool atendimentoUrgente, int x, int y);
    string getNome() { return nome; };
    int getNivelSaude() { return nivelSaude; };
    bool getAtendimentoUrgente() { return atendimentoUrgente; };
    int getX() { return x; };
    int getY() { return y; };
    void setX(int novoX) { x = novoX; }
    void setY(int novoY) { y = novoY; }
    string toString();
};

#endif