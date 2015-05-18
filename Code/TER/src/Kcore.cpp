#include "Kcore.h"

using namespace std;

//les degr�s des sommets du kcore en fonction de k
std::vector<int> Kcore::kcore(GrapheNonOriente* graphe, int k){
    std::vector<int> tabdegre;//tableau de degr�s des sommets
    for(int i=0;i<graphe->size();i++){
       tabdegre.push_back(graphe->getDegre(i));
    }
    while(!supK(tabdegre,k)){//tant qu'il reste des degr�s inf�rieurs � k et diff�rents de 0
        for(int i=0;i<graphe->size();i++){
            if(tabdegre[i]<k && tabdegre[i]!=0){
                tabdegre[i] = 0;//on passe le degr� du sommet � 0 vu qu'il n'appartient pas au kcore
                std::vector<Arc> arcs = graphe->getArcs(i);
                for (int j=0;j<arcs.size();j++){
                    //on r�cup�re les voisins et on diminuent leur degr� de 1
                    Arc a = arcs[j];
                    if(tabdegre[a.getNumeroSommet()] != 0)
                        tabdegre[a.getNumeroSommet()]--;
                }
            }
        }
    }
    return tabdegre;
}

//v�rifie si tous les degr�s sont sup�rieurs ou �gals � k
bool Kcore::supK (std::vector<int> tabdegre, int k){
    for(int i=0;i<tabdegre.size();i++){
        if(tabdegre[i]<k && tabdegre[i]!=0){
            return false;
        }
    }
    return true;
}


