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

//Retourne la taille du graphe (nombre de sommets)
int Graphe::size() const{
    return l_degrescumulatifs.size();
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int Graphe::getPoids(int const& numero_sommet) const{
    if (numero_sommet >= 0 && numero_sommet < l_poids.size()){
        return l_poids[numero_sommet];
    }
    return -1;
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int Graphe::getDegreSortant(int const& numero_sommet) const{
    if(numero_sommet == 0){
        return l_degrescumulatifs[numero_sommet];
    }else if(numero_sommet > 0 && numero_sommet < size()){
        return l_degrescumulatifs[numero_sommet] - l_degrescumulatifs[numero_sommet-1];
    }
    return -1;
}

//Retourne -1 si le numéro du sommet n'est pas dans le graphe
int Graphe::getDegreEntrant(int const& numero_sommet) const{
    if (numero_sommet >= 0 && numero_sommet < size()){
        int degre = 0;
        for(int i=0; i<l_arcs.size(); i++){
            if(l_arcs[i] == numero_sommet){
                degre++;
            }
        }
        return degre;
    }
    return -1;
}

std::vector<int> Graphe::getArcsSortants(int const& numero_sommet) const{
    std::vector<int> arcs;
    if (numero_sommet >= 0 && numero_sommet < size()){
        int startIndice, endIndice(l_degrescumulatifs[numero_sommet]);
        if(numero_sommet == 0){
            startIndice = 0;
        }else{
            startIndice = l_degrescumulatifs[numero_sommet-1];
        }
        for(int i=startIndice; i<endIndice; i++){
            arcs.push_back(l_arcs[i]);
        }
    }
    return arcs;
}

std::vector<int> Graphe::getArcsEntrants(int const& numero_sommet) const{
    std::vector<int> arcs;
    if (numero_sommet >= 0 && numero_sommet < size()){
        //On cherche les arcs pour tous les sommets du graphe
        for(int sommet=0; sommet<size(); sommet++){
            int startIndice, endIndice(l_degrescumulatifs[sommet]);
            if(sommet == 0){
                startIndice = 0;
            }else{
                startIndice = l_degrescumulatifs[sommet-1];
            }
            //On regarde si le sommet à un arc sortant vers notre sommet
            for(int i=startIndice; i<endIndice; i++){
                if(l_arcs[i] == numero_sommet){
                    //Si le numéro de sommet pour lequel on cherche les arcs entrants est dans la liste des arcs sortants d'un sommet,
                    //on ajoute ce sommet à la liste des arcs entrants de notre sommet et on passe au prochain sommet(break)
                    arcs.push_back(sommet);
                    break;
                }
            }
        }
    }
    return arcs;
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
    	cout << numero1.getPoids(i) << " ";
    }
    cout << endl;
    cout << "Graphe 1 - Degres sortants : ";
    for (int i(0); i<(numero1.size()); i++)
    {
    	cout << numero1.getDegreSortant(i) << " ";
    }
    cout << endl;
    cout << "Graphe 1 - Degres entrants : ";
    for (int i(0); i<(numero1.size()); i++)
    {
    	cout << numero1.getDegreEntrant(i) << " ";
    }
    cout << endl;
    cout << "Graphe 1 - Arcs sortants : " << endl;
    for (int i(0); i<(numero1.size()); i++)
    {
    	std::vector<int> arcs = numero1.getArcsSortants(i);
    	cout << " Sommet num " << i << " : ";
    	for(int i=0; i<arcs.size(); i++){
            cout << arcs[i] << " ";
    	}
    	cout << endl;
    }
    cout << endl;
    cout << "Graphe 1 - Arcs entrants : " << endl;
    for (int i(0); i<(numero1.size()); i++)
    {
    	std::vector<int> arcs = numero1.getArcsEntrants(i);
    	cout << " Sommet num " << i << " : ";
    	for(int i=0; i<arcs.size(); i++){
            cout << arcs[i] << " ";
    	}
    	cout << endl;
    }
    cout << endl;

	return 0;
}
