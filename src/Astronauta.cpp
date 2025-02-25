#include "Astronauta.hpp"
#include <sstream>

Astronauta::Astronauta(string nome, int nivelSaude, bool atendimentoUrgente, int x, int y)
    : nome(nome), nivelSaude(nivelSaude), atendimentoUrgente(atendimentoUrgente), x(x), y(y) {}

string Astronauta::toString()
{
    ostringstream oss;
    oss << nome << " - Nível de saúde: " << nivelSaude << " - Atendimento urgente: " << (atendimentoUrgente ? "sim" : "não") << " - Posição: (" << x << "," << y << ")";
    return oss.str();
}
