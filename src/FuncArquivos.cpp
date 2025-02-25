#include "FuncArquivos.hpp"
#include "ModuloNormal.hpp"
#include "ModuloComAstronauta.hpp"
#include "ModuloComFogo.hpp"
#include "ModuloObstaculo.hpp"
#include "ModuloSeguranca.hpp"
#include "ModuloVazio.hpp"
#include "EstacaoEspacial.hpp"

void FuncArquivos::lerArquivo(const string &caminhoArquivo, EstacaoEspacial &estacao, RoboDeResgate &robo)
{

    ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << endl;
        return;
    }

    // Dimensões da matriz e leitura da matriz
    string linha;
    int linhas, colunas;

    getline(arquivo, linha);
    istringstream dimensoes(linha);
    dimensoes >> linhas >> colunas;

    estacao.setLinhas(linhas);
    estacao.setColunas(colunas);

    vector<vector<Modulo *>> &matriz = estacao.getMatriz();
    matriz.resize(linhas, vector<Modulo *>(colunas, nullptr));

    for (int i = 0; i < linhas; i++)
    {
        getline(arquivo, linha);
        for (int j = 0; j < colunas; j++)
        {
            char tipo = linha[j];
            switch (tipo)
            {
            case '.':
                matriz[i][j] = new ModuloNormal(tipo);
                break;
            case 'A':
                matriz[i][j] = new ModuloComAstronauta(tipo);
                break;
            case 'F':
                matriz[i][j] = new ModuloComFogo(tipo);
                break;
            case '#':
                matriz[i][j] = new ModuloObstaculo(tipo);
                break;
            case 'S':
                robo.setPosicaoInicialX(i);
                robo.setPosicaoInicialY(j);
                matriz[i][j] = new ModuloSeguranca(tipo);
                break;
            case '~':
                matriz[i][j] = new ModuloVazio(tipo);
                break;
            }
        }
    }

    bool lendoPosicoes = false;
    // Leitura das informações dos astronautas
    while (getline(arquivo, linha))
    {
        if (linha == "Astronautas:")
        {
            continue;
        }

        if (linha == "Posicoes dos astronautas na matriz:")
        {
            lendoPosicoes = true;
            continue;
        }

        if (!lendoPosicoes)
        {
            istringstream streamLinha(linha);
            string nome;
            int nivelDeSaude;
            bool atendimentoMedicoUrgente;
            char separador;

            getline(streamLinha, nome, ',');
            streamLinha >> nivelDeSaude >> separador >> atendimentoMedicoUrgente;

            estacao.getAstronautas().emplace_back(Astronauta(nome, nivelDeSaude, atendimentoMedicoUrgente, 0, 0));
        }

        else
        {
            istringstream streamLinha(linha);
            string nome;
            int x, y;

            getline(streamLinha, nome, ':');

            string lixo, coords;
            getline(streamLinha, lixo, '(');
            getline(streamLinha, coords, ')');

            stringstream ss(coords);
            char separador;
            ss >> x >> separador >> y;

            if (matriz[x][y]->getTipo() != 'A')
            {
                cout << "Posição inválida para o astronauta " + nome + ". Posição: (" + to_string(x) + ", " + to_string(y) + "). \n";
                exit(1);
            }

            for (auto &astronauta : estacao.getAstronautas())
            {
                if (astronauta.getNome() == nome)
                {
                    astronauta.setX(x);
                    astronauta.setY(y);
                    break;
                }
            }
        }
    }

    robo.setEstacao(estacao);
    arquivo.close();
}

void FuncArquivos::escreverArquivo(const string &caminhoArquivo, RoboDeResgate &robo)
{
    ofstream arquivo(caminhoArquivo);

    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo: resgate.txt" << endl;
        return;
    }

    arquivo << "Relatório de resgate:" << endl
            << endl
            << endl;
    arquivo << "Número de astronautas resgatados: " << robo.getResgatados().size() << endl
            << endl;

    for (Astronauta astronauta : robo.getResgatados())
    {
        arquivo << astronauta.toString() << endl;
    }

    arquivo << endl
            << endl;
    arquivo << "Número de astronautas não resgatados: " << robo.getNaoResgatados().size() << endl
            << endl;

    for (Astronauta astronauta : robo.getNaoResgatados())
    {
        arquivo << astronauta.toString() << endl;
    }

    arquivo << endl
            << "Tempo total da operação de resgate: " << robo.getPassos() << endl;
    arquivo.close();
}