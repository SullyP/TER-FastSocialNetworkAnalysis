#include "GrapheOriente.h"

using namespace std;

GrapheOriente::GrapheOriente(string const& p_nom){
    string name = "graphes/"+p_nom;

	ifstream fichier(name.c_str(), ios::in);

	if(fichier)
        {
				vector< vector<Arc> > v_entrant;
				vector< vector<Arc> > v_sortant;
				vector<Arc> arcs_entrants;
				vector<Arc> arcs_sortants;
				vector<int> deg_entrants;
				vector<int> deg_sortants;
				string ligne;
     		    while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
       			{
					char c = ligne[0];
					if(c!='%'){
						istringstream iss(ligne);
						string word;
						int cpt=0;
						int value1;
						int value2;
						while(cpt<2 && iss >> word){
							if (cpt==0){
								value1 = atoi(word.c_str());
							}
							else{
								value2 = atoi(word.c_str());
							}
							cpt++;
						}
						if((unsigned)value1>v_entrant.size()){
							vector<Arc> y_entrant;
							vector<Arc> y_sortant;
							v_entrant.push_back(y_entrant);
							v_sortant.push_back(y_sortant);
						}
						if((unsigned)value2>v_entrant.size()){
							vector<Arc> y_entrant;
							vector<Arc> y_sortant;
							v_entrant.push_back(y_entrant);
							v_sortant.push_back(y_sortant);
						}
						v_sortant[value1-1].push_back(Arc(1,value2-1));
						v_entrant[value2-1].push_back(Arc(1,value1-1));
					}
				}
				int cpt_sortant=0;
				int cpt_entrant=0;
				for(unsigned int i=0;i<v_sortant.size();i++){
					vector<Arc> sortant = v_sortant[i];
					vector<Arc> entrant = v_entrant[i];
					for(unsigned int j=0;j<sortant.size();j++){
						arcs_sortants.push_back(sortant[j]);
					}
					cpt_sortant+=sortant.size();
					deg_sortants.push_back(cpt_sortant);
					for(unsigned int j=0;j<entrant.size();j++){
						arcs_entrants.push_back(entrant[j]);
					}
					cpt_entrant+=entrant.size();
					deg_entrants.push_back(cpt_entrant);
				}
                vector<double> poids;

                m_poidsTotalArcs = 0.0;

                for(unsigned int i=0; i<poids.size(); i++){
                    m_poids.push_back(poids[i]);
                }
                for(unsigned int i=0; i<arcs_entrants.size(); i++){
                    m_arcsEntrants.push_back(arcs_entrants[i]);
                    m_poidsTotalArcs += arcs_entrants[i].getPoids();
                }
                for(unsigned int i=0; i<arcs_sortants.size(); i++){
                    m_arcsSortants.push_back(arcs_sortants[i]);
                    if(arcs_sortants[i].getNumeroSommet() != i){
                        m_poidsTotalArcs += arcs_sortants[i].getPoids();
                    }
                }
                for(unsigned int i=0; i<deg_entrants.size(); i++){
                    m_degresCumulatifsEntrants.push_back(deg_entrants[i]);
                }
                for(unsigned int i=0; i<deg_sortants.size(); i++){
                    m_degresCumulatifsSortants.push_back(deg_sortants[i]);
                }

				//graph = new GrapheOriente(deg_sortants,deg_entrants,arcs_sortants,arcs_entrants,poids);
                fichier.close();
        }
	else{
		cout << " Fichier inexistant " << endl;
	}
}

GrapheOriente::GrapheOriente(std::vector<int> const& p_degresCumulatifsSortants, std::vector<int> const& p_degresCumulatifsEntrants, std::vector<Arc> const& p_arcsSortants, std::vector<Arc> const& p_arcsEntrants, std::vector<double> const& p_poids){
    m_poidsTotalArcs = 0.0;
    for(unsigned int i=0; i<p_poids.size(); i++){
        m_poids.push_back(p_poids[i]);
    }
    for(unsigned int i=0; i<p_arcsEntrants.size(); i++){
        m_arcsEntrants.push_back(p_arcsEntrants[i]);
        m_poidsTotalArcs += p_arcsEntrants[i].getPoids();
    }
    for(unsigned int i=0; i<p_arcsSortants.size(); i++){
        m_arcsSortants.push_back(p_arcsSortants[i]);
        if(p_arcsSortants[i].getNumeroSommet() != i){
            m_poidsTotalArcs += p_arcsSortants[i].getPoids();
        }
    }
    for(unsigned int i=0; i<p_degresCumulatifsEntrants.size(); i++){
        m_degresCumulatifsEntrants.push_back(p_degresCumulatifsEntrants[i]);
    }
    for(unsigned int i=0; i<p_degresCumulatifsSortants.size(); i++){
        m_degresCumulatifsSortants.push_back(p_degresCumulatifsSortants[i]);
    }
}

GrapheOriente::~GrapheOriente(){
    //dtor
}

unsigned int GrapheOriente::nbArcs() const{
    return m_arcsSortants.size();
}

int GrapheOriente::getDegreBoucle(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    std::vector<Arc> arcs;
    int degreBoucle = 0;

    //On effectue la recherche dans la liste d'arcs qui comporte le moinds d'éléments
    if(getDegreEntrant(p_numeroSommet) < getDegreSortant(p_numeroSommet)){
        arcs = getArcsEntrants(p_numeroSommet);
    }else{
        arcs = getArcsSortants(p_numeroSommet);
    }

    for(unsigned int indice = 0; indice < arcs.size(); indice++){
        //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on incrémente le dégré
        if(arcs[indice].getNumeroSommet() == p_numeroSommet){
            degreBoucle++;
        }
    }

    return degreBoucle;
}

//Retourne la taille du graphe (nombre de sommets)
unsigned int GrapheOriente::size() const{
    return m_degresCumulatifsSortants.size();
}

int GrapheOriente::getDegreSortant(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    if(p_numeroSommet == 0){
        return m_degresCumulatifsSortants[p_numeroSommet];
    }else{
        return m_degresCumulatifsSortants[p_numeroSommet] - m_degresCumulatifsSortants[p_numeroSommet-1];
    }
}

int GrapheOriente::getDegreEntrant(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    if(p_numeroSommet == 0){
        return m_degresCumulatifsEntrants[p_numeroSommet];
    }else{
        return m_degresCumulatifsEntrants[p_numeroSommet] - m_degresCumulatifsEntrants[p_numeroSommet-1];
    }
}

std::vector<Arc> GrapheOriente::getArcsSortants(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    std::vector<Arc> arcs;
    int startIndice, endIndice(m_degresCumulatifsSortants[p_numeroSommet]);
    if(p_numeroSommet == 0){
        startIndice = 0;
    }else{
        startIndice = m_degresCumulatifsSortants[p_numeroSommet-1];
    }
    for(int i=startIndice; i<endIndice; i++){
        arcs.push_back(m_arcsSortants[i]);
    }
    return arcs;
}

std::vector<Arc> GrapheOriente::getArcsEntrants(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    std::vector<Arc> arcs;
    int startIndice, endIndice(m_degresCumulatifsEntrants[p_numeroSommet]);
    if(p_numeroSommet == 0){
        startIndice = 0;
    }else{
        startIndice = m_degresCumulatifsEntrants[p_numeroSommet-1];
    }
    for(int i=startIndice; i<endIndice; i++){
        arcs.push_back(m_arcsEntrants[i]);
    }
    return arcs;
}

double GrapheOriente::getSommePoidsBoucle(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    double sommePoidsBoucle = 0;
    std::vector<Arc> arcs;

    //On effectue la recherche dans la liste d'arcs qui comporte le moins d'éléments
    if(getDegreEntrant(p_numeroSommet) < getDegreSortant(p_numeroSommet)){
        arcs = getArcsEntrants(p_numeroSommet);
    }else{
        arcs = getArcsSortants(p_numeroSommet);
    }

    for(unsigned int indice = 0; indice < arcs.size(); indice++){
        //Lorsque l'on trouve un arc qui part du sommet pour arriver sur lui-même, on ajoute le poids de l'arc
        if(arcs[indice].getNumeroSommet() == p_numeroSommet){
            sommePoidsBoucle += arcs[indice].getPoids();
        }
    }

    return sommePoidsBoucle;
}

double GrapheOriente::getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    double sommePoidsArcsEntrants = 0;
    std::vector<Arc> arcs = getArcsEntrants(p_numeroSommet);

    for(unsigned int indice = 0; indice < arcs.size(); indice++){
            sommePoidsArcsEntrants += arcs[indice].getPoids();
    }

    return sommePoidsArcsEntrants;
}

double GrapheOriente::getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const{
    assert(p_numeroSommet < size());

    double sommePoidsArcsSortants = 0;
    std::vector<Arc> arcs = getArcsSortants(p_numeroSommet);

    for(unsigned int indice = 0; indice < arcs.size(); indice++){
            sommePoidsArcsSortants += arcs[indice].getPoids();
    }

    return sommePoidsArcsSortants;
}
