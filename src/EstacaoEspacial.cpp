#include "EstacaoEspacial.hpp"
#include <iostream>

void EstacaoEspacial::imprimirMatriz() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << matriz[i][j]->getTipo() << " ";
        }
        cout << endl;
    }
}