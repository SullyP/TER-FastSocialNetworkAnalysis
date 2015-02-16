#include "structure.hpp"

using namespace std;

Graphe::Graphe ()
{

}

int Graphe::ajouterDansG1 (int& nombre)
{
	g_arcs.push_back(nombre);
	return 0;
}

int Graphe::ajouterDansG2 (int& nombre)
{
	g_degrescumulatifs.push_back(nombre);
	return 0;
}

int Graphe::ajouterDansG3 (int& nombre)
{
	g_troisiemetableau.push_back(nombre);
	return 0;
}

void Graphe::remplirValeur (int& choix1, int& valeur)
{
	vector<int> arcs = this->g_arcs;
	vector<int> degrescumulatifs = this->g_degrescumulatifs;
	vector<int> troisiemetableau = this->g_troisiemetableau;

	if (choix1 == 1)
    {
    	this->ajouterDansG1(valeur);
    }
    else if (choix1 == 2)
    {
    	this->ajouterDansG2(valeur);
    }
    else if (choix1 == 3)
    {
    	this->ajouterDansG3(valeur);
    }
    cout << choix1 << endl;
}

int Graphe::getTailleG1()
{
	return this->g_arcs.size();
}
int Graphe::getTailleG2()
{
	return this->g_degrescumulatifs.size();
}
int Graphe::getTailleG3()
{
	return this->g_troisiemetableau.size();
}

std::vector<int>* Graphe::getG1()
{
	return &(this->g_arcs);
}
std::vector<int>* Graphe::getG2()
{
	return &(this->g_degrescumulatifs);
}
std::vector<int>* Graphe::getG3()
{
	return &(this->g_troisiemetableau);
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

	std::vector<int>* g_arcs = numero1.getG1();
	std::vector<int>* g_degrescumulatifs = numero1.getG2();
	std::vector<int>* g_troisiemetableau = numero1.getG3();

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

	cout << "Graphe 1 - g_arcs : ";
    for (int i(0); i<(numero1.getTailleG1()); i++)
    {
    	cout << (*g_arcs)[i] << " ";
    }
    cout << endl;
    cout << "Graphe 1 - g_degrescumulatifs : ";
    for (int i(0); i<(numero1.getTailleG2()); i++)
    {
    	cout << (*g_degrescumulatifs)[i] << " ";
    }
    cout << endl;
    cout << "Graphe 1 - g_troisiemetableau : ";
    for (int i(0); i<(numero1.getTailleG3()); i++)
    {
    	cout << (*g_troisiemetableau)[i] << " ";
    }
    cout << endl;
	return 0;
}