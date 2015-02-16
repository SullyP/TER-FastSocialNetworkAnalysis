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
    int ajouterDansG1(int& nombre);
    int ajouterDansG2(int& nombre);
    int ajouterDansG3(int& nombre);
    void remplirValeur(int& choix, int& valeur);
    int getTailleG1();
    int getTailleG2();
    int getTailleG3();
    std::vector<int>* getG1();
    std::vector<int>* getG2();
    std::vector<int>* getG3();
    //retirerDeG1();
    //retirerDeG2();
    //retirerDeG3();
    //void recevoirDegats(int nbDegats);

	private:

	std::vector<int> g_arcs;
 	std::vector<int> g_degrescumulatifs;
	std::vector<int> g_troisiemetableau;
};