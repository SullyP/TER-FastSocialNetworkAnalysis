#include "Kcore.h"

using namespace std;

//les degrés des sommets du kcore en fonction de k
std::vector<int> Kcore::kcore(GrapheNonOriente* graphe, int k){
    std::vector<int> tabdegre;//tableau de degrés des sommets
    for(int i=0;i<graphe->size();i++){
       tabdegre.push_back(graphe->getDegre(i));
    }
    while(!supK(tabdegre,k)){//tant qu'il reste des degrés inférieurs à k et différents de 0
        for(int i=0;i<graphe->size();i++){
            if(tabdegre[i]<k && tabdegre[i]!=0){
                tabdegre[i] = 0;//on passe le degré du sommet à 0 vu qu'il n'appartient pas au kcore
                std::vector<Arc> arcs = graphe->getArcs(i);
                for (int j=0;j<arcs.size();j++){
                    //on récupère les voisins et on diminuent leur degré de 1
                    Arc a = arcs[j];
                    if(tabdegre[a.getNumeroSommet()] != 0)
                        tabdegre[a.getNumeroSommet()]--;
                }
            }
        }
    }
    return tabdegre;
}

//vérifie si tous les degrés sont supérieurs ou égals à k
bool Kcore::supK (std::vector<int> tabdegre, int k){
    for(int i=0;i<tabdegre.size();i++){
        if(tabdegre[i]<k && tabdegre[i]!=0){
            return false;
        }
    }
    return true;
}


