#include "GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente(std::vector<int> const& p_degresCumulatifs, std::vector<int> const& p_arcs, std::vector<int> const& p_poids){
    for(unsigned int i=0; i<p_poids.size(); i++){
        m_poids.push_back(p_poids[i]);
    }
    for(unsigned int i=0; i<p_arcs.size(); i++){
        m_arcs.push_back(p_arcs[i]);
    }
    for(unsigned int i=0; i<p_degresCumulatifs.size(); i++){
        m_degresCumulatifs.push_back(p_degresCumulatifs[i]);
    }
}

GrapheNonOriente::~GrapheNonOriente(){
    //dtor
}

unsigned int GrapheNonOriente::size() const{
    return m_degresCumulatifs.size();
}

int GrapheNonOriente::getDegreSortant(unsigned int const& p_numeroSommet) const{
    return getDegre(p_numeroSommet);
}

int GrapheNonOriente::getDegreEntrant(unsigned int const& p_numeroSommet) const{
    return getDegre(p_numeroSommet);
}

std::vector<int> GrapheNonOriente::getArcsSortants(unsigned int const& p_numeroSommet) const{
    return getArcs(p_numeroSommet);
}

std::vector<int> GrapheNonOriente::getArcsEntrants(unsigned int const& p_numeroSommet) const{
    return getArcs(p_numeroSommet);
}

std::vector<int> GrapheNonOriente::getArcs(unsigned int const& p_numeroSommet) const{
    std::vector<int> arcs;
    if (p_numeroSommet < size()){
        int startIndice, endIndice(m_degresCumulatifs[p_numeroSommet]);
        if(p_numeroSommet == 0){
            startIndice = 0;
        }else{
            startIndice = m_degresCumulatifs[p_numeroSommet-1];
        }
        for(int i=startIndice; i<endIndice; i++){
            arcs.push_back(m_arcs[i]);
        }
    }
    return arcs;
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int GrapheNonOriente::getDegre(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet == 0){
        return m_degresCumulatifs[p_numeroSommet];
    }else if(p_numeroSommet < size()){
        return m_degresCumulatifs[p_numeroSommet] - m_degresCumulatifs[p_numeroSommet-1];
    }
    return -1;
}
