
#ifndef ESTACAOESPACIAL_HPP
#define ESTACAOESPACIAL_HPP
#include <list>
#include <vector>
#include "Astronauta.hpp"
#include "Modulo.hpp"

using namespace std;

class EstacaoEspacial
{
protected:
    vector<vector<Modulo *>> matriz;
    list<Astronauta> astronautas;
    int linhas;
    int colunas;

public:
    EstacaoEspacial() : linhas(0), colunas(0)
    {
        matriz = vector<vector<Modulo *>>();
        astronautas = list<Astronauta>();
    }

    void imprimirMatriz();
    
    vector<vector<Modulo *>> &getMatriz() { return matriz; }
    void setMatriz(vector<vector<Modulo *>> &novaMatriz) { matriz = novaMatriz; }

    list<Astronauta> &getAstronautas() { return astronautas; }
    void setAstronautas(list<Astronauta> &novosAstronautas) { astronautas = novosAstronautas; }

    int getLinhas() const { return linhas; }
    void setLinhas(int novasLinhas) { linhas = novasLinhas; }

    int getColunas() const { return colunas; }
    void setColunas(int novasColunas) { colunas = novasColunas; }

};

#endif
