#include <iostream>
#include "RoboDeResgate.hpp"
#include "EstacaoEspacial.hpp"
#include "FuncArquivos.hpp"
#include "Astronauta.hpp"

using namespace std;

int main()
{
    for (int i = 1; i <= 10; i++)
    {   
        cout << endl << endl << endl<< endl << "Caminho mapaaaa " << i << ": " << endl;
        string nomeArquivo = "./entradas/entrada" + to_string(i) + ".txt";
        string nomeArquivoS = "./saidas/saida" + to_string(i) + ".txt";
        EstacaoEspacial estacao;
        FuncArquivos arq;
        RoboDeResgate roboDeResgate;
        arq.lerArquivo(nomeArquivo, estacao, roboDeResgate);
        roboDeResgate.iniciarResgate();
        arq.escreverArquivo(nomeArquivoS, roboDeResgate);
    }
    

    return 0;
}