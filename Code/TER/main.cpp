#include <iostream>
#include "GrapheOriente.h"
#include "GrapheNonOriente.h"

using namespace std;

int main()
{
    vector<int> degresCumulatifsSortants;
    vector<int> degresCumulatifsEntrants;
    vector<int> arcsSortants;
    vector<int> arcsEntrants;
    vector<int> poids;
    //Exemple lors de la première réunion de TER
    degresCumulatifsSortants.push_back(1);
    degresCumulatifsSortants.push_back(3);
    degresCumulatifsSortants.push_back(4);
    degresCumulatifsSortants.push_back(4);
    degresCumulatifsEntrants.push_back(0);
    degresCumulatifsEntrants.push_back(2);
    degresCumulatifsEntrants.push_back(3);
    degresCumulatifsEntrants.push_back(4);
    arcsSortants.push_back(1);
    arcsSortants.push_back(2);
    arcsSortants.push_back(3);
    arcsSortants.push_back(1);
    arcsEntrants.push_back(0);
    arcsEntrants.push_back(2);
    arcsEntrants.push_back(1);
    arcsEntrants.push_back(1);
    GrapheOriente* grapheOriente = new GrapheOriente(degresCumulatifsSortants,degresCumulatifsEntrants,arcsSortants,arcsEntrants,poids);

    cout << "Graphe Oriente - Degres sortants : ";
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
    	cout << grapheOriente->getDegreSortant(i) << " ";
    }
    cout << endl;
    cout << "Graphe Oriente - Degres entrants : ";
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
    	cout << grapheOriente->getDegreEntrant(i) << " ";
    }
    cout << endl;
    cout << "Graphe Oriente - Arcs sortants : " << endl;
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
    	std::vector<int> arcs = grapheOriente->getArcsSortants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << arcs[i] << " ";
    	}
    	cout << endl;
    }
    cout << endl;
    cout << "Graphe Oriente - Arcs entrants : " << endl;
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
    	std::vector<int> arcs = grapheOriente->getArcsEntrants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << arcs[i] << " ";
    	}
    	cout << endl;
    }
    cout << endl;

    GrapheNonOriente* grapheNonOriente = grapheOriente->convertToGrapheNonOriente();

    cout << "Graphe Non-Oriente - Degres : ";
    for (unsigned int i=0; i<grapheNonOriente->size(); i++)
    {
    	cout << grapheNonOriente->getDegreEntrant(i) << " ";
    }
    cout << endl;
    cout << "Graphe Non-Oriente - Arcs : " << endl;
    for (unsigned int i=0; i<grapheNonOriente->size(); i++)
    {
    	std::vector<int> arcs = grapheNonOriente->getArcsSortants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << arcs[i] << " ";
    	}
    	cout << endl;
    }
    cout << endl;


    cout << "BFS GrapheOriente - Tous les sommets a partir de 0" << endl;
    vector<bool> bfs = grapheOriente->breadthFirstSearch(0);
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
        if(bfs[i]){
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "BFS grapheNonOriente - Tous les sommets sauf le 1, a partir de 0" << endl;
    vector<int> nePasPrendreEnCompte;
    nePasPrendreEnCompte.push_back(1);
    vector<bool> bfs2 = grapheNonOriente->breadthFirstSearch(0,nePasPrendreEnCompte);
    for (unsigned int i=0; i<grapheNonOriente->size(); i++)
    {
        if(bfs2[i]){
            cout << i << " ";
        }
    }
    cout << endl;

    delete grapheNonOriente;
    delete grapheOriente;
    return 0;
}
