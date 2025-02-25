#ifndef FUNCARQUVIOS_HPP
#define FUNCARQUVIOS_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include "Modulo.hpp"
#include "Astronauta.hpp"
#include "EstacaoEspacial.hpp"
#include "RoboDeResgate.hpp"

using namespace std;
class FuncArquivos
{
public:
    void lerArquivo(const string &caminhoArquivo, EstacaoEspacial &estacao, RoboDeResgate &robo);
    void escreverArquivo(const string &caminhoArquivo, RoboDeResgate &robo);
};

#endif 
