#include "GuimeraAmaral.h"

GuimeraAmaral::GuimeraAmaral(std::vector<int> const& p_noeudCommunaute, std::vector< std::vector<int> > const& p_communauteNoeud, const Graphe* p_graphe){
    m_noeudCommunaute = p_noeudCommunaute;
    m_communauteNoeud = p_communauteNoeud;
    m_graphe = p_graphe;

    m_degreEntrantCommunaute.resize(m_graphe->size());
    m_degreMoyenEntrantCommunaute.resize(m_communauteNoeud.size());
    m_ecartTypeEntrantCommunaute.resize(m_communauteNoeud.size());

    #pragma omp parallel for
    for (unsigned int numeroSommet=0; numeroSommet < m_graphe->size(); numeroSommet++) {
            m_degreEntrantCommunaute[numeroSommet] = degreEntrantCommunaute(numeroSommet, m_noeudCommunaute[numeroSommet]);
            if(m_graphe->estOriente()){
                //Si le graphe est orienté, on doit aussi calculé pour les arcs sortants
                m_degreSortantCommunaute[numeroSommet] = degreSortantCommunaute(numeroSommet, m_noeudCommunaute[numeroSommet]);
            }
    }

    #pragma omp parallel for
    for (unsigned int numeroCommunaute=0; numeroCommunaute < m_communauteNoeud.size(); numeroCommunaute++) {
            m_degreMoyenEntrantCommunaute[numeroCommunaute] = degreMoyenEntrantCommunaute(numeroCommunaute);
            m_ecartTypeEntrantCommunaute[numeroCommunaute] = ecartTypeEntrantCommunaute(numeroCommunaute);
            if(m_graphe->estOriente()){
                //Si le graphe est orienté, on doit aussi calculé pour les arcs sortants
                m_degreMoyenSortantCommunaute[numeroCommunaute] = degreMoyenSortantCommunaute(numeroCommunaute);
                m_ecartTypeSortantCommunaute[numeroCommunaute] = ecartTypeSortantCommunaute(numeroCommunaute);
            }
    }
}

// Calcule la variance entrante
double GuimeraAmaral::varianceEntrante(int const& p_numeroCommunaute) const{
    double moyenne = m_degreMoyenEntrantCommunaute[p_numeroCommunaute];
    double tmp = 0;
    #pragma omp parallel for reduction(+:tmp)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
        double degreNoeud = m_degreEntrantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
        double tmpBis = degreNoeud - moyenne;
        tmp += tmpBis*tmpBis;
    }
    return (tmp/(double)m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule la variance sortante
double GuimeraAmaral::varianceSortante(int const& p_numeroCommunaute) const{
    double moyenne = m_degreMoyenSortantCommunaute[p_numeroCommunaute];
    double tmp = 0;
    #pragma omp parallel for reduction(+:tmp)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
        double degreNoeud = m_degreSortantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
        double tmpBis = degreNoeud - moyenne;
        tmp += tmpBis*tmpBis;
    }
    return (tmp/(double)m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre moyen entrant d'une communaute
double GuimeraAmaral::degreMoyenEntrantCommunaute(int const& p_numeroCommunaute) const{
    long degreGlobalCommu = 0;
    #pragma omp parallel for reduction(+:degreGlobalCommu)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += m_degreEntrantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre moyen sortant d'une communaute
double GuimeraAmaral::degreMoyenSortantCommunaute(int const& p_numeroCommunaute) const{
    long degreGlobalCommu = 0;
    #pragma omp parallel for reduction(+:degreGlobalCommu)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += m_degreSortantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre interne/entrant d'un noeud
int GuimeraAmaral::degreEntrantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute) const{
    int degreIntCom = 0;
    std::vector<Arc> voisins = m_graphe->getArcsEntrants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (m_noeudCommunaute[voisins[i].getNumeroSommet()] == p_numeroCommunaute)
            degreIntCom++;
    }
    return degreIntCom;
}

// Calcule le degre sortant d'un noeud
int GuimeraAmaral::degreSortantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute) const{
    int degreIntCom = 0;
    std::vector<Arc> voisins = m_graphe->getArcsSortants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (m_noeudCommunaute[voisins[i].getNumeroSommet()] == p_numeroCommunaute)
            degreIntCom++;
    }
    return degreIntCom;
}

// Calcule l'ecart type entrant
double GuimeraAmaral::ecartTypeEntrantCommunaute(int const& p_numeroCommunaute) const{
    return sqrt(varianceEntrante(p_numeroCommunaute));
}

// Calcule l'ecart type sortant
double GuimeraAmaral::ecartTypeSortantCommunaute(int const& p_numeroCommunaute) const{
    if(m_graphe->estOriente()){
        return sqrt(varianceSortante(p_numeroCommunaute));
    }else{
        return ecartTypeEntrantCommunaute(p_numeroCommunaute);
    }
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreEntrantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute)  const{
    if (m_ecartTypeEntrantCommunaute[p_numeroCommunaute]==0)
       return 0;
    else
       return ((m_degreEntrantCommunaute[p_numeroSommet]-m_degreMoyenEntrantCommunaute[p_numeroCommunaute])/m_ecartTypeEntrantCommunaute[p_numeroCommunaute]);
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreSortantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute)  const{
    if(m_graphe->estOriente()){
        if (m_ecartTypeSortantCommunaute[p_numeroCommunaute]==0)
           return 0;
        else
           return ((m_degreSortantCommunaute[p_numeroSommet]-m_degreMoyenSortantCommunaute[p_numeroCommunaute])/m_ecartTypeSortantCommunaute[p_numeroCommunaute]);
    }else{
        return zScoreEntrantCommunaute(p_numeroSommet, p_numeroCommunaute);
    }
}

// Retourne oui si le noeud est un hub, non sinon
bool GuimeraAmaral::estHub(int const& p_numeroSommet, int const& p_numeroCommunaute) const{
    return (zScoreEntrantCommunaute(p_numeroSommet, p_numeroCommunaute))>=2.5;
}

double GuimeraAmaral::participationExterne(int const& p_numeroSommet) const{
    //Un vecteur de taille égale au nombre de communautés, rempli de 0
    vector<unsigned int> degreCommunautes(m_communauteNoeud.size(),0);

	// Parcours du voisinage des noeuds
	// A la fin, le vecteur contient le degre du noeud vers chaque communaute
	vector<Arc> voisins = m_graphe->getArcsSortants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
                degreCommunautes[m_noeudCommunaute[voisins[i].getNumeroSommet()]]++;
	}

	double sum = 0.;
	double const degreSortant = m_graphe->getDegreSortant(p_numeroSommet);

	// Parcours du vecteur de communautes pour calculer la participation
	for(unsigned int numeroCommunaute = 0; numeroCommunaute < degreCommunautes.size(); numeroCommunaute++) {
		// Si le noeud a des voisins dans la communaute
		if(degreCommunautes[numeroCommunaute] > 0) {
            sum += ((double)(degreCommunautes[numeroCommunaute]) / degreSortant) * ((double)(degreCommunautes[numeroCommunaute]) / degreSortant);
		}
	}

	return (1 - sum);
}

double GuimeraAmaral::participationInterne(int const& p_numeroSommet) const{
    //Un vecteur de taille égale au nombre de communautés, rempli de 0
    vector<unsigned int> degreCommunautes(m_communauteNoeud.size(),0);

	// Parcours du voisinage des noeuds
	// A la fin, le vecteur contient le degre du noeud vers chaque communaute
	vector<Arc> voisins = m_graphe->getArcsEntrants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
                degreCommunautes[m_noeudCommunaute[voisins[i].getNumeroSommet()]]++;
	}

	double sum = 0.;
	double const degreSortant = m_graphe->getDegreEntrant(p_numeroSommet);

	// Parcours du vecteur de communautes pour calculer la participation
	for(unsigned int numeroCommunaute = 0; numeroCommunaute < degreCommunautes.size(); numeroCommunaute++) {
		// Si le noeud a des voisins dans la communaute
		if(degreCommunautes[numeroCommunaute] > 0) {
            sum += ((double)(degreCommunautes[numeroCommunaute]) / degreSortant) * ((double)(degreCommunautes[numeroCommunaute]) / degreSortant);
		}
	}

	return (1 - sum);
}

// Retourne oui si le noeud est peripherique, non sinon
bool GuimeraAmaral::estPeripherique(int const& p_numeroSommet) const{
    return ((zScoreEntrantCommunaute(p_numeroSommet, m_noeudCommunaute[p_numeroSommet]))<2.5
            && participationExterne(p_numeroSommet) <= 0.62);
}

// Retourne oui si le noeud est ultra-peripherique, non sinon
bool GuimeraAmaral::estUltraPeripherique(int const& p_numeroSommet) const{
    return ((zScoreEntrantCommunaute(p_numeroSommet, m_noeudCommunaute[p_numeroSommet]))<2.5
            && participationExterne(p_numeroSommet) <= 0.05);
}

Connectivite GuimeraAmaral::connectiviteNoeud(int const& p_numeroSommet) const{
    double p = participationExterne(p_numeroSommet);
    double z = zScoreEntrantCommunaute(p_numeroSommet, m_noeudCommunaute[p_numeroSommet]);
    if(z >= 2.5){
        if(p <= 0.3){
            return FAIBLE;
        }else if(p <= 0.75){
            return FORT;
        }else{
            return TRESFORT;
        }
    }else{
        if(p <= 0.05){
            return TRESFAIBLE;
        }else if(p <= 0.62){
            return FAIBLE;
        }else if(p <= 0.8){
            return FORT;
        }else{
            return TRESFORT;
        }
    }
}

//Getters
vector<int> GuimeraAmaral::getNoeudCommunaute() const{
    return m_noeudCommunaute;
}
vector< vector<int> > GuimeraAmaral::getCommunauteNoeud() const{
    return m_communauteNoeud;
}
vector<int> GuimeraAmaral::getDegreEntrantCommunaute() const{
    return m_degreEntrantCommunaute;
}
vector<double> GuimeraAmaral::getDegreMoyenEntrantCommunaute() const{
    return m_degreMoyenEntrantCommunaute;
}
vector<double> GuimeraAmaral::getEcartTypeEntrantCommunaute() const{
    return m_ecartTypeEntrantCommunaute;
}
vector<int> GuimeraAmaral::getDegreSortantCommunaute() const{
    if(m_graphe->estOriente()){
        return m_degreSortantCommunaute;
    }else{
        return m_degreEntrantCommunaute;
    }
}
vector<double> GuimeraAmaral::getDegreMoyenSortantCommunaute() const{
    if(m_graphe->estOriente()){
        return m_degreMoyenSortantCommunaute;
    }else{
        return m_degreMoyenEntrantCommunaute;
    }
}
vector<double> GuimeraAmaral::getEcartTypeSortantCommunaute() const{
    if(m_graphe->estOriente()){
        return m_ecartTypeSortantCommunaute;
    }else{
        return m_ecartTypeEntrantCommunaute;
    }
}
const Graphe* GuimeraAmaral::getGraphe() const{
    return m_graphe;
}
