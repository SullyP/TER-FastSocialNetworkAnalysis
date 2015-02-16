#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>

int ajouteDeux(int& nombreRecu);
void echange(double& a, double& b);

class Graphe
{
    public:

    Graphe();
    int ajouterDansL1(int& nombre);
    int ajouterDansL2(int& nombre);
    int ajouterDansL3(int& nombre);
    void remplirValeur(int& choix, int& valeur);
    int getTailleL1();
    int getTailleL2();
    int getTailleL3();
    std::vector<int>* getL1();
    std::vector<int>* getL2();
    std::vector<int>* getL3();

	private:

	std::vector<int> l_arcs;
 	std::vector<int> l_degrescumulatifs;
	std::vector<int> l_poids;
};