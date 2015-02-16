#include "structure.hpp"

using namespace std;

Graphe::Graphe ()
{

}

int Graphe::ajouterDansL1 (int& nombre)
{
	l_arcs.push_back(nombre);
	return 0;
}

int Graphe::ajouterDansL2 (int& nombre)
{
	l_degrescumulatifs.push_back(nombre);
	return 0;
}

int Graphe::ajouterDansL3 (int& nombre)
{
	l_poids.push_back(nombre);
	return 0;
}

void Graphe::remplirValeur (int& choix1, int& valeur)
{
	vector<int> arcs = this->l_arcs;
	vector<int> degrescumulatifs = this->l_degrescumulatifs;
	vector<int> poids = this->l_poids;

	if (choix1 == 1)
    {
    	this->ajouterDansL1(valeur);
    }
    else if (choix1 == 2)
    {
    	this->ajouterDansL2(valeur);
    }
    else if (choix1 == 3)
    {
    	this->ajouterDansL3(valeur);
    }
}

int Graphe::getTailleL1()
{
	return this->l_arcs.size();
}
int Graphe::getTailleL2()
{
	return this->l_degrescumulatifs.size();
}
int Graphe::getTailleL3()
{
	return this->l_poids.size();
}

std::vector<int>* Graphe::getL1()
{
	return &(this->l_arcs);
}
std::vector<int>* Graphe::getL2()
{
	return &(this->l_degrescumulatifs);
}
std::vector<int>* Graphe::getL3()
{
	return &(this->l_poids);
}

int choixListe ()
{
	cout << "Ajouter des valeurs au graphe 1" << endl;
	cout << "> 1 : dans la liste des arcs" << endl;
	cout << "> 2 : dans la liste des degres cumulatifs" << endl;
	cout << "> 3 : dans le tableau" << endl;
	cout << "> 0 : ne plus ajouter de valeur" << endl;

	int choix1(0); 
    cin >> choix1; 

    return choix1;
}

int choixValeur ()
{
	cout << "Valeur ?" << endl;

    int valeur(0); 
    cin >> valeur;

    return valeur; 
}

int main ()
{
	Graphe numero1;

	int choix1 = 0;

	std::vector<int>* l_arcs = numero1.getL1();
	std::vector<int>* l_degrescumulatifs = numero1.getL2();
	std::vector<int>* l_poids = numero1.getL3();

	do 
    {
    	choix1 = choixListe();
        if(choix1 != 0)
        {
        	int valeur = choixValeur();
    		numero1.remplirValeur(choix1, valeur);
    	}
    }    
    while (choix1!=0);

	cout << "Graphe 1 - l_arcs : ";
    for (int i(0); i<(numero1.getTailleL1()); i++)
    {
    	cout << (*l_arcs)[i] << " ";
    }
    cout << endl;
    cout << "Graphe 1 - l_degrescumulatifs : ";
    for (int i(0); i<(numero1.getTailleL2()); i++)
    {
    	cout << (*l_degrescumulatifs)[i] << " ";
    }
    cout << endl;
    cout << "Graphe 1 - l_poids : ";
    for (int i(0); i<(numero1.getTailleL3()); i++)
    {
    	cout << (*l_poids)[i] << " ";
    }
    cout << endl;
	return 0;
}
