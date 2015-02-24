#include "Graphe.h"

Graphe::~Graphe(){
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int Graphe::getPoids(unsigned int const& p_numeroSommet) const{
    if (p_numeroSommet < m_poids.size()){
        return m_poids[p_numeroSommet];
    }
    return -1;
}
