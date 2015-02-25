#include "Graphe.h"

Graphe::~Graphe(){
}

//Retourne -1 si le num�ro du sommet n'est pas dans le graphe
int Graphe::getPoids(unsigned int const& p_numeroSommet) const{
    if (p_numeroSommet < m_poids.size()){
        return m_poids[p_numeroSommet];
    }
    return -1;
}

/*
    Effectue une recherche en largeur sur le graphe.
    @param p_numeroSommet Num�ro du sommet � partir duquel commencer la recherche
    @param p_sommetsANePasPrendreEnCompte Liste des sommets � ne pas prendre en compte lors de la recherche, comme s'ils ne faissaient pas partis du graphe. (OPTIONNEL)
    @return Renvoie une liste de bool�en pour chaque sommet du graphe, vrai si le sommet � �t� trouver lors de la recherche, faux sinon.
*/
std::vector<bool> Graphe::breadthFirstSearch(unsigned int const& p_numeroSommet, std::vector<int> const& p_sommetsANePasPrendreEnCompte) const{
    std::vector<bool> sommetsAPrendreEnCompte(size(),true);
    std::vector<bool> marquer(size(),false);
    std::queue<int> file;

    for(unsigned int i=0; i<p_sommetsANePasPrendreEnCompte.size(); i++){
        sommetsAPrendreEnCompte[p_sommetsANePasPrendreEnCompte[i]] = false;
    }

    //On ajoute le sommet de d�part � la file et on le marque
    file.push(p_numeroSommet);
    marquer[p_numeroSommet] = true;

    //Tant qu'il reste des sommets � visiter
    while(!file.empty()){
        std::vector<int> voisins = getArcsSortants(file.front());
        file.pop();
        //Pour chaque voisin
        for(unsigned int i=0; i<voisins.size(); i++){
            int sommetVoisin = voisins[i];
            //Si le sommet doit �tre pris en compte par l'algorithme et s'il n'est pas d�j� marqu�
            if(sommetsAPrendreEnCompte[sommetVoisin] && !marquer[sommetVoisin]){
                file.push(sommetVoisin);
                marquer[sommetVoisin] = true;
            }
        }
    }

    return marquer;
}
