#include "RoboDeResgate.hpp"
#include "EstacaoEspacial.hpp"
#include "ModuloObstaculo.hpp"
#include <iostream>
#include <algorithm>
#include <queue>

RoboDeResgate::RoboDeResgate() : posicaoInicialX(0), posicaoInicialY(0), passos(0), estacao(), resgatados(), naoResgatados() {}

bool RoboDeResgate::proximoAoFogo(int x, int y)
{
    int directions[][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        if (newX >= 0 && newX < estacao.getLinhas() && newY >= 0 && newY < estacao.getColunas())
        {
            Modulo *adjacente = estacao.getMatriz()[newX][newY];
            if (adjacente != nullptr && adjacente->getTipo() == 'F')
            {
                return true;
            }
        }
    }
    return false;
}

bool RoboDeResgate::dentroDosLimites(int x, int y)
{
    int linhas = estacao.getLinhas();
    int colunas = estacao.getColunas();
    return x >= 0 && x < linhas && y >= 0 && y < colunas;
}

bool RoboDeResgate::podeAcessar(int x, int y)
{
    if (estacao.getMatriz()[x][y]->getTipo() == '#' || estacao.getMatriz()[x][y]->getTipo() == '~' || estacao.getMatriz()[x][y]->getTipo() == 'F')
    {
        return false;
    }
    return true;
}

void RoboDeResgate::resgatarAstronauta(Posicao atual)
{
    for (auto astronauta : estacao.getAstronautas())
    {
        if (astronauta.getX() == atual.x && astronauta.getY() == atual.y)
        {
            cout << endl
                 << astronauta.toString() << endl;
            resgatados.push_back(astronauta);
            break;
        }
    }
}

int RoboDeResgate::iniciarResgate()
{
    int linhas = estacao.getLinhas();
    int colunas = estacao.getColunas();

    int Xinit = this->posicaoInicialX;
    int Yinit = this->posicaoInicialY;

    Posicao base = {posicaoInicialX, posicaoInicialY};
    bool resgatando = true;

    while (true)
    {
        vector<vector<bool>> visitado(linhas, vector<bool>(colunas, false));
        vector<vector<Posicao>> anterior(linhas, vector<Posicao>(colunas, {-1, -1}));

        Posicao ultimoEncontrado;
        vector<Posicao> caminho = {};
        queue<Posicao> fila = {};

        fila.push({Xinit, Yinit});
        visitado[Xinit][Yinit] = true;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        Posicao destino = {-1, -1};

        while (!fila.empty())
        {
            Posicao atual = fila.front();
            fila.pop();

            if (proximoAoFogo(atual.x, atual.y))
            {
                cout << "Inicio próximo ao fogo. Todo mundo morreu!" << endl;
                identificarNaoResgatados();
                return 0;
            }
            // Se estamos resgatando astronautas
            if (resgatando && estacao.getMatriz()[atual.x][atual.y]->getTipo() == 'A' &&
                !(ultimoEncontrado.x == atual.x && ultimoEncontrado.y == atual.y))
            {
                resgatarAstronauta(atual);
                estacao.getMatriz()[atual.x][atual.y]->setTipo('E');
                ultimoEncontrado = atual;
                destino = atual;
                break;
            }

            // Se não há mais astronautas, ir para a base
            if (!resgatando && atual.x == base.x && atual.y == base.y)
            {
                identificarNaoResgatados();
                return 0;
            }

            for (int i = 0; i < 4; i++)
            {
                int nx = atual.x + dx[i];
                int ny = atual.y + dy[i];

                if (dentroDosLimites(nx, ny) && !visitado[nx][ny] && podeAcessar(nx, ny) && !proximoAoFogo(nx, ny))
                {
                    visitado[nx][ny] = true;
                    anterior[nx][ny] = atual;
                    fila.push({nx, ny});
                }
            }
        }

        // Se não encontrou astronautas, muda o objetivo para a base
        if (destino.x == -1 && destino.y == -1)
        {
            cout << endl
                 << "Retornando para a base." << endl;
            if (resgatando)
            {
                resgatando = false;
                destino = base;
            }
        }

        // Reconstrução do caminho
        for (Posicao p = destino; p.x != -1 && p.y != -1; p = anterior[p.x][p.y])
        {
            caminho.push_back(p);
        }
        reverse(caminho.begin(), caminho.end());

        imprimirCaminho(caminho);

        Xinit = caminho.back().x;
        Yinit = caminho.back().y;
    }
}

void RoboDeResgate::identificarNaoResgatados()
{

    for (auto astronauta : estacao.getAstronautas())
    {
        bool resgatado = false;
        for (auto astronautaResgatado : resgatados)
        {
            if (astronauta.getNome() == astronautaResgatado.getNome())
            {
                resgatado = true;
                break;
            }
        }
        if (!resgatado)
        {
            naoResgatados.push_back(astronauta);
        }
    }
    cout << endl
         << "Nao resgatados: " << endl;
    for (auto astronauta : naoResgatados)
    {
        cout << astronauta.toString() << endl;
    }
}

void RoboDeResgate::imprimirCaminho(vector<Posicao> &caminho)
{
    for (int i = 0; i < estacao.getLinhas(); i++)
    {
        for (int j = 0; j < estacao.getColunas(); j++)
        {
            bool ehCaminho = false;
            unsigned int idx = 0;
            for (const auto &p : caminho)
            {
                if (p.x == i && p.y == j)
                {
                    ehCaminho = true;
                    break;
                }
                idx++;
            }

            if (ehCaminho && idx != 0 && idx != caminho.size() - 1)
            {
                cout << "* ";
            }
            else
            {
                if (estacao.getMatriz()[i][j]->getTipo() == 'E')
                {
                    cout << "A ";
                }
                else
                {
                    cout << estacao.getMatriz()[i][j]->getTipo() << " ";
                }
            }
        }
        cout << endl;
    }
    this->passos += caminho.size() - 1;
    cout << "Passos: " << caminho.size() - 1 << endl;
    cout << "Total de Passos: " << passos << endl;
}
