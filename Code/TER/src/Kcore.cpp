#include "Kcore.h"

using namespace std;

//vérifie si tous les degrés sont supérieurs ou égals à k
bool Kcore::supK (std::vector<int> tabdegre, int k){
    for(unsigned int i=0;i<tabdegre.size();i++){
        if(tabdegre[i]<k && tabdegre[i]!=0){
            return false;
        }
    }
    return true;
}

Kcore::Kcore(GrapheNonOriente* graphe, int k){
    std::vector<int> degresCumulatifs;
    std::vector<int> tabdegre;//tableau de degrés des sommets
    for(unsigned int i=0;i<graphe->size();i++){
       tabdegre.push_back(graphe->getDegre(i));
    }
    while(!supK(tabdegre,k)){//tant qu'il reste des degrés inférieurs à k et différents de 0
        for(unsigned int i=0;i<graphe->size();i++){
            if(tabdegre[i]<k && tabdegre[i]!=0){
                tabdegre[i] = 0;//on passe le degré du sommet à 0 vu qu'il n'appartient pas au kcore
                std::vector<Arc> arcs = graphe->getArcs(i);
                for (unsigned int j=0;j<arcs.size();j++){
                    //on récupère les voisins et on diminuent leur degré de 1
                    Arc a = arcs[j];
                    if(tabdegre[a.getNumeroSommet()] != 0)
                        tabdegre[a.getNumeroSommet()]--;
                }
            }
        }
    }
    //calcul degrés cumultatifs
    for(unsigned int i=0;i<graphe->size();i++){
        if(i == 0){
            degresCumulatifs.push_back(tabdegre[i]);
        }else{
            degresCumulatifs.push_back(tabdegre[i] + degresCumulatifs[i-1]);
        }
    }
    //construction de graphe
    std::vector<Arc> arcsG;
    std::vector<double> poids;
    unsigned int nbArcs = graphe->nbArcs();
    for(unsigned int numeroSommet=0; numeroSommet<graphe->size();numeroSommet++){
        if(tabdegre[numeroSommet] == 0){
            //On dérément le nombre d'arcs car ce sommet n'a plus d'arcs
            nbArcs -= graphe->getDegre(numeroSommet);
        }else{
            vector<Arc> voisins = graphe->getArcs(numeroSommet);
            for(unsigned int indiceVoisin=0; indiceVoisin < voisins.size(); indiceVoisin++){
                    if(tabdegre[(voisins[indiceVoisin]).getNumeroSommet()] != 0){
                        //Si le voisin a toujours des arcs, alors on ajoute l'arc
                        arcsG.push_back(voisins[indiceVoisin]);
                    }
            }
        }
    }

    m_grapheKcore = new GrapheNonOriente(degresCumulatifs, arcsG, poids, nbArcs);
    m_tabDegre = tabdegre;
}

vector<int> Kcore::getTabDegre() const{
    return m_tabDegre;
}
GrapheNonOriente* Kcore::getGrapheKcore() const{
    return m_grapheKcore;
}
