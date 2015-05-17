#include "GuimeraAmaral.h"

// ecartTypeInterne[i] = ecartTypeInt(i);
// degreMoyenInterneCommu[i] = degreMoyenIntCom(i);
// degreInterneCommu[i] = degreIntCom(i);// Calcule la variance interne (?)

GuimeraAmaral::GuimeraAmaral(Communaute const& p_communaute){
    m_noeudCommunaute = p_communaute.getNoeudCommunaute();
    m_communauteNoeud = p_communaute.getCommunauteNoeud();
    m_graphe = p_communaute.getGraphe();

    m_degreInterneCommunaute.resize(m_graphe->size());
    m_degreMoyenInterneCommunaute.resize(m_communauteNoeud.size());
    m_ecartTypeInterneCommunaute.resize(m_communauteNoeud.size());

    #pragma omp parallel for
    for (unsigned int numeroSommet=0; numeroSommet < m_graphe->size(); numeroSommet++) {
            m_degreInterneCommunaute[numeroSommet] = degreIntCom(numeroSommet, m_noeudCommunaute[numeroSommet]);
    }

    #pragma omp parallel for
    for (unsigned int numeroCommunaute=0; numeroCommunaute < m_communauteNoeud.size(); numeroCommunaute++) {
            m_degreMoyenInterneCommunaute[numeroCommunaute] = degreMoyenIntCom(numeroCommunaute);
            m_ecartTypeInterneCommunaute[numeroCommunaute] = ecartTypeInt(numeroCommunaute);
    }
}

// Calcule la variance interne
double GuimeraAmaral::varianceInt(int p_numeroCommunaute){
    double moyenne = m_degreMoyenInterneCommunaute[p_numeroCommunaute];
    double tmp = 0;
    #pragma omp parallel for reduction(+:tmp)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
        double degreNoeud = m_degreInterneCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
        double tmpBis = degreNoeud - moyenne;
        tmp += tmpBis*tmpBis;
    }
    return (tmp/(double)m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre moyen interne d'une communaute
double GuimeraAmaral::degreMoyenIntCom(int p_numeroCommunaute){
    long degreGlobalCommu = 0;
    #pragma omp parallel for reduction(+:degreGlobalCommu)
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += m_degreInterneCommunaute[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre interne/entrant d'un noeud
int GuimeraAmaral::degreIntCom(int p_numeroSommet, int p_numeroCommunaute){
    int degreIntCom = 0;
    std::vector<Arc> voisins = m_graphe->getArcsEntrants(p_numeroSommet);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (m_noeudCommunaute[voisins[i].getNumeroSommet()] == p_numeroCommunaute)
            degreIntCom++;
    }
    return degreIntCom;
}

// Calcule l'ecart type interne (?)
double GuimeraAmaral::ecartTypeInt(int p_numeroCommunaute){
    return sqrt(varianceInt(p_numeroCommunaute));
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreInt(int p_numeroSommet, int p_numeroCommunaute){
    if (m_ecartTypeInterneCommunaute[p_numeroCommunaute]==0)
       return 0;
    else
       return ((m_degreInterneCommunaute[p_numeroSommet]-m_degreMoyenInterneCommunaute[p_numeroCommunaute])/m_ecartTypeInterneCommunaute[p_numeroCommunaute]);
}

// Retourne oui si le noeud est un hub, non sinon
bool GuimeraAmaral::estHub(int p_numeroSommet, int p_numeroCommunaute){
    return (zScoreInt(p_numeroSommet, p_numeroCommunaute))>=2.5;
}

// Retourne le nombre de connexions entre deux communautes
int GuimeraAmaral::connexions(int p_numeroCommunauteA, int p_numeroCommunauteB){
    return 0;
}

// Retourne oui si le noeud est peripherique, non sinon
bool GuimeraAmaral::estPeriph(int p_numeroSommet){
    return false;
}
