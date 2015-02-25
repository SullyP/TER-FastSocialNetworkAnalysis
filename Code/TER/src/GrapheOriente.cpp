#include "GrapheOriente.h"
#include <iostream>

GrapheOriente::GrapheOriente(std::vector<int> const& p_degresCumulatifsSortants, std::vector<int> const& p_degresCumulatifsEntrants, std::vector<int> const& p_arcsSortants, std::vector<int> const& p_arcsEntrants, std::vector<int> const& p_poids){
    for(unsigned int i=0; i<p_poids.size(); i++){
        m_poids.push_back(p_poids[i]);
    }
    for(unsigned int i=0; i<p_arcsEntrants.size(); i++){
        m_arcsEntrants.push_back(p_arcsEntrants[i]);
    }
    for(unsigned int i=0; i<p_arcsSortants.size(); i++){
        m_arcsSortants.push_back(p_arcsSortants[i]);
    }
    for(unsigned int i=0; i<p_degresCumulatifsEntrants.size(); i++){
        m_degresCumulatifsEntrants.push_back(p_degresCumulatifsEntrants[i]);
    }
    for(unsigned int i=0; i<p_degresCumulatifsSortants.size(); i++){
        m_degresCumulatifsSortants.push_back(p_degresCumulatifsSortants[i]);
    }
}

GrapheOriente::~GrapheOriente(){
    //dtor
}

//Créé une instance de GrapheNonOriente à partir du graphe orienté
GrapheNonOriente* GrapheOriente::convertToGrapheNonOriente() const{
    std::vector<int> degresCumulatifs(size());
    std::vector<int> arcs(m_arcsEntrants.size() + m_arcsSortants.size());
    unsigned int numeroSommet;

    //Remplissage de degresCumulatifs et arcs
    #pragma omp parallel for private(numeroSommet) schedule(dynamic)
    for(numeroSommet=0; numeroSommet<size(); numeroSommet++){
        std::vector<int> arcsEntrants = getArcsEntrants(numeroSommet);
        std::vector<int> arcsSortants = getArcsSortants(numeroSommet);

        //Degré du sommet en non-orienté
        degresCumulatifs[numeroSommet] = m_degresCumulatifsEntrants[numeroSommet] + m_degresCumulatifsSortants[numeroSommet];

        //Indices pour l'ajout des arcs dans le tableau
        int startIndice,changeIndice,endIndice;
        if(numeroSommet == 0){
            startIndice = 0;
        }else{
            startIndice = m_degresCumulatifsEntrants[numeroSommet-1] + m_degresCumulatifsSortants[numeroSommet-1];
        }
        changeIndice = startIndice + arcsEntrants.size();
        endIndice = changeIndice + arcsSortants.size();

        //Ajout des arcs
        int indice;
        #pragma omp parallel for private(indice) schedule(dynamic)
        for(indice=startIndice; indice<endIndice; indice++){
            if(indice < changeIndice){
                arcs[indice] = arcsEntrants[indice - startIndice];
            }else{
                arcs[indice] = arcsSortants[indice - changeIndice];
            }
        }
    }

    return new GrapheNonOriente(degresCumulatifs, arcs, m_poids);
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
