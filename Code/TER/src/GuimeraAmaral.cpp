#include "GuimeraAmaral.h"

// ecartTypeInterne[i] = ecartTypeInt(i);
// degreMoyenInterneCommu[i] = degreMoyenIntCom(i);
// degreInterneCommu[i] = degreIntCom(i);// Calcule la variance interne (?)

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
double GuimeraAmaral::varianceEntrante(int p_numeroCommunaute){
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
double GuimeraAmaral::varianceSortante(int p_numeroCommunaute){
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
double GuimeraAmaral::degreMoyenEntrantCommunaute(int p_numeroCommunaute){
    long degreGlobalCommu = 0;
    #pragma omp parallel for reduction(+:degreGlobalCommu)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += m_degreEntrantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre moyen sortant d'une communaute
double GuimeraAmaral::degreMoyenSortantCommunaute(int p_numeroCommunaute){
    long degreGlobalCommu = 0;
    #pragma omp parallel for reduction(+:degreGlobalCommu)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += m_degreSortantCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre interne/entrant d'un noeud
int GuimeraAmaral::degreEntrantCommunaute(int p_numeroSommet, int p_numeroCommunaute){
    int degreIntCom = 0;
    std::vector<Arc> voisins = m_graphe->getArcsEntrants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (m_noeudCommunaute[voisins[i].getNumeroSommet()] == p_numeroCommunaute)
            degreIntCom++;
    }
    return degreIntCom;
}

// Calcule le degre sortant d'un noeud
int GuimeraAmaral::degreSortantCommunaute(int p_numeroSommet, int p_numeroCommunaute){
    int degreIntCom = 0;
    std::vector<Arc> voisins = m_graphe->getArcsSortants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (m_noeudCommunaute[voisins[i].getNumeroSommet()] == p_numeroCommunaute)
            degreIntCom++;
    }
    return degreIntCom;
}

// Calcule l'ecart type entrant
double GuimeraAmaral::ecartTypeEntrantCommunaute(int p_numeroCommunaute){
    return sqrt(varianceEntrante(p_numeroCommunaute));
}

// Calcule l'ecart type sortant
double GuimeraAmaral::ecartTypeSortantCommunaute(int p_numeroCommunaute){
    if(m_graphe->estOriente()){
        return sqrt(varianceSortante(p_numeroCommunaute));
    }else{
        return ecartTypeEntrantCommunaute(p_numeroCommunaute);
    }
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreEntrantCommunaute(int p_numeroSommet, int p_numeroCommunaute){
    if (m_ecartTypeEntrantCommunaute[p_numeroCommunaute]==0)
       return 0;
    else
       return ((m_degreEntrantCommunaute[p_numeroSommet]-m_degreMoyenEntrantCommunaute[p_numeroCommunaute])/m_ecartTypeEntrantCommunaute[p_numeroCommunaute]);
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreSortantCommunaute(int p_numeroSommet, int p_numeroCommunaute){
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
bool GuimeraAmaral::estHub(int p_numeroSommet, int p_numeroCommunaute){
    return (zScoreEntrantCommunaute(p_numeroSommet, p_numeroCommunaute))>=2.5;
}

// Retourne le nombre de connexions entre deux communautes
int GuimeraAmaral::connexions(int p_numeroCommunauteA, int p_numeroCommunauteB){
    return 0;
}

// Retourne oui si le noeud est peripherique, non sinon
bool GuimeraAmaral::estPeriph(int p_numeroSommet){
    return false;
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
