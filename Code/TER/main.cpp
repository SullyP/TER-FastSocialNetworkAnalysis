#include <iostream>
#include "GrapheOriente.h"
#include "GrapheNonOriente.h"
#include "IndiceEnsembliste.h"
#include "ParticipationExterne.h"
#include "Lecture.h"

using namespace std;

int main()
{
    vector<int> degresCumulatifsSortants;
    vector<int> degresCumulatifsEntrants;
    vector<Arc> arcsSortants;
    vector<Arc> arcsEntrants;
    vector<double> poids;
    //Exemple lors de la première réunion de TER avec une boucle sur le 3eme sommet
    degresCumulatifsSortants.push_back(1);
    degresCumulatifsSortants.push_back(3);
    degresCumulatifsSortants.push_back(4);
    degresCumulatifsSortants.push_back(5);
    degresCumulatifsEntrants.push_back(0);
    degresCumulatifsEntrants.push_back(2);
    degresCumulatifsEntrants.push_back(3);
    degresCumulatifsEntrants.push_back(5);
    arcsSortants.push_back(Arc(1,1));
    arcsSortants.push_back(Arc(1,2));
    arcsSortants.push_back(Arc(1,3));
    arcsSortants.push_back(Arc(1,1));
    arcsSortants.push_back(Arc(1,3));
    arcsEntrants.push_back(Arc(1,0));
    arcsEntrants.push_back(Arc(1,2));
    arcsEntrants.push_back(Arc(1,1));
    arcsEntrants.push_back(Arc(1,1));
    arcsEntrants.push_back(Arc(1,3));

    GrapheOriente* grapheOriente = new GrapheOriente("out.brunson_revolution_revolution");

    cout << "Graphe Oriente - Taille : " << grapheOriente->size() << endl;
    cout << "Graphe Oriente - Nombre d'arcs : " << grapheOriente->nbArcs() << endl;
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
    	std::vector<Arc> arcs = grapheOriente->getArcsSortants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << "poids: " << arcs[i].getPoids() << " sommet: " << arcs[i].getNumeroSommet() << " ";
    	}
    	cout << endl;
    }
    cout << endl;
    cout << "Graphe Oriente - Arcs entrants : " << endl;
    for (unsigned int i=0; i<grapheOriente->size(); i++)
    {
    	std::vector<Arc> arcs = grapheOriente->getArcsEntrants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << "poids: " << arcs[i].getPoids() << " sommet: " << arcs[i].getNumeroSommet() << " ";
    	}
    	cout << endl;
    }
    cout << "Graphe Oriente - Degre double pour le sommet 1 : " << grapheOriente->getDegreBoucle(1) << endl;
    cout << "Graphe Oriente - Degre double pour le sommet 3 : " << grapheOriente->getDegreBoucle(3) <<  endl;
    cout << "Graphe Oriente - Somme des poids des boucles du sommet 3 : " << grapheOriente->getSommePoidsBoucle(3) <<  endl;
    cout << "Graphe Oriente - Somme des poids des arcs entrants du sommet 2 : " << grapheOriente->getSommePoidsArcsEntrants(2) <<  endl;
    cout << "Graphe Oriente - Somme des poids des arcs sortants du sommet 2 : " << grapheOriente->getSommePoidsArcsSortants(2) <<  endl;
    cout << endl;

    GrapheNonOriente* grapheNonOriente = new GrapheNonOriente(*grapheOriente);

    cout << "Graphe Non-Oriente - Taille : " << grapheNonOriente->size() << endl;
    cout << "Graphe Non-Oriente - Nombre d'arcs : " << grapheNonOriente->nbArcs() << endl;
    cout << "Graphe Non-Oriente - Degres : ";
    for (unsigned int i=0; i<grapheNonOriente->size(); i++)
    {
    	cout << grapheNonOriente->getDegreEntrant(i) << " ";
    }
    cout << endl;
    cout << "Graphe Non-Oriente - Arcs : " << endl;
    for (unsigned int i=0; i<grapheNonOriente->size(); i++)
    {
    	std::vector<Arc> arcs = grapheNonOriente->getArcsSortants(i);
    	cout << " Sommet num " << i << " : ";
    	for(unsigned int i=0; i<arcs.size(); i++){
            cout << "poids: " << arcs[i].getPoids() << " sommet: " << arcs[i].getNumeroSommet() << " ";
    	}
    	cout << endl;
    }
    cout << "Graphe Non-Oriente - Degre double pour le sommet 1 : " << grapheNonOriente->getDegreBoucle(1) << endl;
    cout << "Graphe Non-Oriente - Degre double pour le sommet 3 : " << grapheNonOriente->getDegreBoucle(3) <<  endl;
    cout << "Graphe Non-Oriente - Somme des poids des boucles du sommet 3 : " << grapheNonOriente->getSommePoidsBoucle(3) <<  endl;
    cout << "Graphe Non-Oriente - Somme des poids des arcs du sommet 2 : " << grapheNonOriente->getSommePoidsArcs(2) <<  endl;
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

    vector<int> ensembleA, ensembleB;
    ensembleA.push_back(1);
    ensembleA.push_back(4);
    ensembleA.push_back(7);
    ensembleB.push_back(4);
    ensembleB.push_back(2);
    IndiceEnsembliste* indiceEnsembliste = new IndiceEnsembliste(ensembleA,ensembleB);

    cout << "ensembleA " << endl;
    for(unsigned int i=0; i<ensembleA.size(); i++){
        cout << ensembleA[i] << " ";
    }
    cout << endl;

    cout << "ensembleB " << endl;
    for(unsigned int i=0; i<ensembleB.size(); i++){
        cout << ensembleB[i] << " ";
    }
    cout << endl;

    cout << " Jacard " << indiceEnsembliste->jaccard() << endl;
    cout << " Overlap Index " << indiceEnsembliste->overlapIndex() << endl;

    Communaute com = Communaute(grapheNonOriente, 5, 1);
    com.effectuerUneEtape();
    participationExterne(com, 1);

    delete indiceEnsembliste;
    delete grapheNonOriente;
    delete grapheOriente;
    return 0;
}
