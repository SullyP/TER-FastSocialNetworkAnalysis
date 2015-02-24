#include "GrapheOriente.h"

GrapheOriente::GrapheOriente(){
    //ctor
}

GrapheOriente::~GrapheOriente(){
    //dtor
}

//Retourne la taille du graphe (nombre de sommets)
unsigned int GrapheOriente::size() const{
    return m_degresCumulatifsSortants.size();
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int GrapheOriente::getDegreSortant(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet == 0){
        return m_degresCumulatifsSortants[p_numeroSommet];
    }else if(p_numeroSommet < size()){
        return m_degresCumulatifsSortants[p_numeroSommet] - m_degresCumulatifsSortants[p_numeroSommet-1];
    }
    return -1;
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int GrapheOriente::getDegreEntrant(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet == 0){
        return m_degresCumulatifsEntrants[p_numeroSommet];
    }else if(p_numeroSommet < size()){
        return m_degresCumulatifsEntrants[p_numeroSommet] - m_degresCumulatifsEntrants[p_numeroSommet-1];
    }
    return -1;
}

std::vector<int> GrapheOriente::getArcsSortants(unsigned int const& p_numeroSommet) const{
    std::vector<int> arcs;
    if (p_numeroSommet < size()){
        int startIndice, endIndice(m_degresCumulatifsSortants[p_numeroSommet]);
        if(p_numeroSommet == 0){
            startIndice = 0;
        }else{
            startIndice = m_degresCumulatifsSortants[p_numeroSommet-1];
        }
        for(int i=startIndice; i<endIndice; i++){
            arcs.push_back(m_arcsSortants[i]);
        }
    }
    return arcs;
}

std::vector<int> GrapheOriente::getArcsEntrants(unsigned int const& p_numeroSommet) const{
    std::vector<int> arcs;
    if (p_numeroSommet < size()){
        int startIndice, endIndice(m_degresCumulatifsEntrants[p_numeroSommet]);
        if(p_numeroSommet == 0){
            startIndice = 0;
        }else{
            startIndice = m_degresCumulatifsEntrants[p_numeroSommet-1];
        }
        for(int i=startIndice; i<endIndice; i++){
            arcs.push_back(m_arcsEntrants[i]);
        }
    }
    return arcs;
}
