#ifndef ROBODERESGATE_HPP
#define ROBODERESGATE_HPP
#include <list>
#include "Astronauta.hpp"
#include "EstacaoEspacial.hpp"

class RoboDeResgate
{
protected:
    int posicaoInicialX;
    int posicaoInicialY;
    int passos;
    EstacaoEspacial estacao;
    list<Astronauta> resgatados;
    list<Astronauta> naoResgatados;
    struct Posicao
    {
        int x, y;
    };

    void resgatarAstronauta(Posicao atual);
    void identificarNaoResgatados();
    void imprimirCaminho(vector<Posicao> &caminho);
    bool dentroDosLimites(int x, int y);
    bool podeAcessar(int x, int y);
    bool proximoAoFogo(int x, int y);

public:
    RoboDeResgate();
    int iniciarResgate();
    int getPassos() { return passos; }
    void setPassos(int novosPassos) { passos = novosPassos; }
    EstacaoEspacial &getEstacao() { return estacao; }
    void setEstacao(EstacaoEspacial &novaEstacao) { estacao = novaEstacao; }
    list<Astronauta> &getResgatados() { return resgatados; }
    void setResgatados(list<Astronauta> &novosResgatados) { resgatados = novosResgatados; }
    list<Astronauta> &getNaoResgatados() { return naoResgatados; }
    void setNaoResgatados(list<Astronauta> &novosNaoResgatados) { naoResgatados = novosNaoResgatados; }
    int getPosicaoInicialX() { return posicaoInicialX; }
    int getPosicaoInicialY() { return posicaoInicialY; }
    void setPosicaoInicialX(int novaPosicaoX) { posicaoInicialX = novaPosicaoX; }
    void setPosicaoInicialY(int novaPosicaoY) { posicaoInicialY = novaPosicaoY; }
};

#endif
