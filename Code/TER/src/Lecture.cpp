#include "Lecture.h"
#include "GrapheOriente.h"

using namespace std;

GrapheOriente* lecture(string nom)
{

    GrapheOriente* graph;
    string name = "graphes/"+nom;

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
						bool occur;
						while(cpt<2 && iss >> word){
							if (cpt==0){
								value1 = atoi(word.c_str());
							}
							else{
								value2 = atoi(word.c_str());
							}
							cpt++;
						}
						if(value1>v_entrant.size()){
							vector<Arc> y_entrant;
							vector<Arc> y_sortant;
							v_entrant.push_back(y_entrant);
							v_sortant.push_back(y_sortant);
						}
						if(value2>v_entrant.size()){
							vector<Arc> y_entrant;
							vector<Arc> y_sortant;
							v_entrant.push_back(y_entrant);
							v_sortant.push_back(y_sortant);
						}
						v_sortant[value1-1].push_back(Arc(value2-1,value1-1));
						v_entrant[value2-1].push_back(Arc(value1-1,value2-1));
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
				graph = new GrapheOriente(deg_sortants,deg_entrants,arcs_sortants,arcs_entrants,poids);
                fichier.close();
        }
	else{
		cout << " Fichier inexistant " << endl;
	}
	return graph;
}
