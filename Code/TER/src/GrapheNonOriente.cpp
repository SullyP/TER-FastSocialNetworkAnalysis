#include "GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente(std::vector<int> const& p_degresCumulatifs, std::vector<Arc> const& p_arcs, std::vector<double> const& p_poids, unsigned int p_nbArcs){
    for(unsigned int i=0; i<p_poids.size(); i++){
        m_poids.push_back(p_poids[i]);
    }
    for(unsigned int i=0; i<p_arcs.size(); i++){
        m_arcs.push_back(p_arcs[i]);
    }
    for(unsigned int i=0; i<p_degresCumulatifs.size(); i++){
        m_degresCumulatifs.push_back(p_degresCumulatifs[i]);
    }
    m_nbArcs = p_nbArcs;
}

GrapheNonOriente::GrapheNonOriente(GrapheOriente const& p_graphe){
    m_nbArcs = p_graphe.nbArcs();

    for(unsigned int numeroSommet=0; numeroSommet < p_graphe.size(); numeroSommet++){
        m_poids.push_back(p_graphe.getPoids(numeroSommet));
    }

    int degreCumulatif = 0;
    for(unsigned int numeroSommet=0; numeroSommet < p_graphe.size(); numeroSommet++){
        std::vector<Arc> arcsEntrants = p_graphe.getArcsEntrants(numeroSommet);
        std::vector<Arc> arcsSortants = p_graphe.getArcsSortants(numeroSommet);

        for(unsigned int numeroArc=0; numeroArc < arcsEntrants.size(); numeroArc++){
            m_arcs.push_back(arcsEntrants[numeroArc]);
            degreCumulatif++;
        }
        for(unsigned int numeroArc=0; numeroArc < arcsSortants.size(); numeroArc++){
            //Si l'arc est une boucle, on ne l'ajoute pas puisque nous l'avons déjà ajouté lors du parcours de arcsEntrants
            if(arcsSortants[numeroArc].getNumeroSommet() != numeroSommet){
                m_arcs.push_back(arcsSortants[numeroArc]);
                degreCumulatif++;
            }
        }
        m_degresCumulatifs.push_back(degreCumulatif);
    }

}

GrapheNonOriente::~GrapheNonOriente(){
    //dtor
}

unsigned int GrapheNonOriente::size() const{
    return m_degresCumulatifs.size();
}

unsigned int GrapheNonOriente::nbArcs() const{
    return m_nbArcs;
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int GrapheNonOriente::getDegreBoucle(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        int degreBoucle = 0;

        //Si le nombre d'arcs est égale au nombre d'arcs présent dans la liste divisé par deux, on est sûr qu'il n'y a pas de boucle (arc sur lui-même) pour aucun noeud.
        //En effet, dans notre liste d'arcs on compte chaque arc 2 fois, sauf pour les boucles.
        if((double)nbArcs() != (double)m_arcs.size()/2){
            std::vector<Arc> arcs = getArcs(p_numeroSommet);

            for(unsigned int indice = 0; indice < arcs.size(); indice++){
                //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on incrémente le dégré
                if(arcs[indice].getNumeroSommet() == p_numeroSommet){
                    degreBoucle++;
                }
            }
        }

        return degreBoucle;
    }
    return -1;
}

int GrapheNonOriente::getDegreSortant(unsigned int const& p_numeroSommet) const{
    return getDegre(p_numeroSommet);
}

int GrapheNonOriente::getDegreEntrant(unsigned int const& p_numeroSommet) const{
    return getDegre(p_numeroSommet);
}

std::vector<Arc> GrapheNonOriente::getArcsSortants(unsigned int const& p_numeroSommet) const{
    return getArcs(p_numeroSommet);
}

std::vector<Arc> GrapheNonOriente::getArcsEntrants(unsigned int const& p_numeroSommet) const{
    return getArcs(p_numeroSommet);
}

std::vector<Arc> GrapheNonOriente::getArcs(unsigned int const& p_numeroSommet) const{
    std::vector<Arc> arcs;
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

int GrapheNonOriente::getSommePoidsBoucle(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        int sommePoidsBoucle = 0;

        //Si le nombre d'arcs est égale au nombre d'arcs présent dans la liste divisé par deux, on est sûr qu'il n'y a pas de boucle (arc sur lui-même) pour aucun noeud.
        //En effet, dans notre liste d'arcs on compte chaque arc 2 fois, sauf pour les boucles.
        if((double)nbArcs() != (double)m_arcs.size()/2){
            std::vector<Arc> arcs = getArcs(p_numeroSommet);

            for(unsigned int indice = 0; indice < arcs.size(); indice++){
                //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on ajoute le poids de l'arc
                if(arcs[indice].getNumeroSommet() == p_numeroSommet){
                    sommePoidsBoucle += arcs[indice].getPoids();
                }
            }
        }

        return sommePoidsBoucle;
    }
    return -1;
}

int GrapheNonOriente::getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const{
    return getSommePoidsArcs(p_numeroSommet);
}

int GrapheNonOriente::getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const{
    return getSommePoidsArcs(p_numeroSommet);
}

int GrapheNonOriente::getSommePoidsArcs(unsigned int const& p_numeroSommet) const{
    if(p_numeroSommet < size()){
        int sommePoidsArcs = 0;
        std::vector<Arc> arcs = getArcs(p_numeroSommet);
        for(unsigned int indice = 0; indice < arcs.size(); indice++){
            sommePoidsArcs += arcs[indice].getPoids();
        }

        return sommePoidsArcs;
    }
    return -1;
}
