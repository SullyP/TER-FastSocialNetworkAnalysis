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

//Cr�� une instance de GrapheNonOriente � partir du graphe orient�
GrapheNonOriente* GrapheOriente::convertToGrapheNonOriente() const{
    std::vector<int> degresCumulatifs(size());
    std::vector<int> arcs(m_arcsEntrants.size() + m_arcsSortants.size());
    unsigned int numeroSommet;

    //Remplissage de degresCumulatifs et arcs
    #pragma omp parallel for private(numeroSommet) schedule(dynamic)
    for(numeroSommet=0; numeroSommet<size(); numeroSommet++){
        std::vector<int> arcsEntrants = getArcsEntrants(numeroSommet);
        std::vector<int> arcsSortants = getArcsSortants(numeroSommet);

        //Degr� du sommet en non-orient�
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
            //TODO Erreur les boucles (arcs allant d'un noeud � lui-m�me) sont compt�es 2 fois !
            if(indice < changeIndice){
                arcs[indice] = arcsEntrants[indice - startIndice];
            }else{
                arcs[indice] = arcsSortants[indice - changeIndice];
            }
        }
    }

    return new GrapheNonOriente(degresCumulatifs, arcs, m_poids, nbArcs());
}

unsigned int GrapheOriente::nbArcs() const{
    return m_arcsSortants.size();
}

//Retourne -1 si le num�ro du sommet n'est pas dans le graphe
int GrapheOriente::getDegreBoucle(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        std::vector<int> arcs;
        int degreBoucle = 0;

        //On effectue la recherche dans la liste d'arcs qui comporte le moinds d'�l�ments
        if(getDegreEntrant(p_numeroSommet) < getDegreSortant(p_numeroSommet)){
            arcs = getArcsEntrants(p_numeroSommet);
        }else{
            arcs = getArcsSortants(p_numeroSommet);
        }

        for(unsigned int indice = 0; indice < arcs.size(); indice++){
            //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-m�me, on incr�mente le d�gr�
            if((unsigned)arcs[indice] == p_numeroSommet){
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

//Retourne -1 si le num�ro du sommet n'est pas dans le graphe
int GrapheOriente::getDegreSortant(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet == 0){
        return m_degresCumulatifsSortants[p_numeroSommet];
    }else if(p_numeroSommet < size()){
        return m_degresCumulatifsSortants[p_numeroSommet] - m_degresCumulatifsSortants[p_numeroSommet-1];
    }
    return -1;
}

//Retourne -1 si le num�ro du sommet n'est pas dans le graphe
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
