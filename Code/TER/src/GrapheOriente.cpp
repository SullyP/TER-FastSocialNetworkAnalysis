#include "GrapheOriente.h"
#include <iostream>

GrapheOriente::GrapheOriente(std::vector<int> const& p_degresCumulatifsSortants, std::vector<int> const& p_degresCumulatifsEntrants, std::vector<Arc> const& p_arcsSortants, std::vector<Arc> const& p_arcsEntrants, std::vector<double> const& p_poids){
    m_poidsTotalArcs = 0.0;
    for(unsigned int i=0; i<p_poids.size(); i++){
        m_poids.push_back(p_poids[i]);
    }
    for(unsigned int i=0; i<p_arcsEntrants.size(); i++){
        m_arcsEntrants.push_back(p_arcsEntrants[i]);
        m_poidsTotalArcs += p_arcsEntrants[i].getPoids();
    }
    for(unsigned int i=0; i<p_arcsSortants.size(); i++){
        m_arcsSortants.push_back(p_arcsSortants[i]);
        if(p_arcsSortants[i].getNumeroSommet() != i){
            m_poidsTotalArcs += p_arcsSortants[i].getPoids();
        }
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

unsigned int GrapheOriente::nbArcs() const{
    return m_arcsSortants.size();
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int GrapheOriente::getDegreBoucle(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        std::vector<Arc> arcs;
        int degreBoucle = 0;

        //On effectue la recherche dans la liste d'arcs qui comporte le moinds d'éléments
        if(getDegreEntrant(p_numeroSommet) < getDegreSortant(p_numeroSommet)){
            arcs = getArcsEntrants(p_numeroSommet);
        }else{
            arcs = getArcsSortants(p_numeroSommet);
        }

        for(unsigned int indice = 0; indice < arcs.size(); indice++){
            //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on incrémente le dégré
            if(arcs[indice].getNumeroSommet() == p_numeroSommet){
                degreBoucle++;
            }
        }

        return degreBoucle;
    }
    return -1;
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

std::vector<Arc> GrapheOriente::getArcsSortants(unsigned int const& p_numeroSommet) const{
    std::vector<Arc> arcs;
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

std::vector<Arc> GrapheOriente::getArcsEntrants(unsigned int const& p_numeroSommet) const{
    std::vector<Arc> arcs;
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

double GrapheOriente::getSommePoidsBoucle(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        double sommePoidsBoucle = 0;
        std::vector<Arc> arcs;

        //On effectue la recherche dans la liste d'arcs qui comporte le moins d'éléments
        if(getDegreEntrant(p_numeroSommet) < getDegreSortant(p_numeroSommet)){
            arcs = getArcsEntrants(p_numeroSommet);
        }else{
            arcs = getArcsSortants(p_numeroSommet);
        }

        for(unsigned int indice = 0; indice < arcs.size(); indice++){
            //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on ajoute le poids de l'arc
            if(arcs[indice].getNumeroSommet() == p_numeroSommet){
                sommePoidsBoucle += arcs[indice].getPoids();
            }
        }

        return sommePoidsBoucle;
    }
    return -1;
}

double GrapheOriente::getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        double sommePoidsArcsEntrants = 0;
        std::vector<Arc> arcs = getArcsEntrants(p_numeroSommet);

        for(unsigned int indice = 0; indice < arcs.size(); indice++){
                sommePoidsArcsEntrants += arcs[indice].getPoids();
        }

        return sommePoidsArcsEntrants;
    }
    return -1;
}

double GrapheOriente::getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        double sommePoidsArcsSortants = 0;
        std::vector<Arc> arcs = getArcsSortants(p_numeroSommet);

        for(unsigned int indice = 0; indice < arcs.size(); indice++){
                sommePoidsArcsSortants += arcs[indice].getPoids();
        }

        return sommePoidsArcsSortants;
    }
    return -1;
}
