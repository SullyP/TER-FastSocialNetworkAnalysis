#include "GuimeraAmaral.h"

// ecartTypeInterne[i] = ecartTypeInt(i);
// degreMoyenInterneCommu[i] = degreMoyenIntCom(i);
// degreInterneCommu[i] = degreIntCom(i);// Calcule la variance interne (?)

GuimeraAmaral::GuimeraAmaral(Communaute const& p_communaute){
    m_noeudCommunaute = p_communaute.getNoeudCommunaute();
    m_communauteNoeud = p_communaute.getCommunauteNoeud();
    m_graphe = p_communaute.getGraphe();
}

// Calcule la variance interne
double GuimeraAmaral::varianceInt(int p_numeroCommunaute){
    vector<int> degreInterneCommu;
    vector<double> degreMoyenInterneCommu;
    double moyenne = degreMoyenInterneCommu[p_numeroCommunaute];
    double tmp = 0;
    double tmpBis = 0;
    double degreNoeud = 0;
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
        degreNoeud = degreInterneCommu[m_communauteNoeud[p_numeroCommunaute][i]];
        tmpBis = degreNoeud - moyenne;
        tmp = tmpBis*tmpBis;
    }
    return (tmp/(double)m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre moyen interne/entrant (?) d'une communaute
float GuimeraAmaral::degreMoyenIntCom(int p_numeroCommunaute, vector<int> degreInterneCommu){
    long degreGlobalCommu = 0;
    for (unsigned int i = 0; i < m_communauteNoeud[p_numeroCommunaute].size(); i++){
         degreGlobalCommu += degreInterneCommu[m_communauteNoeud[p_numeroCommunaute][i]];
    }
    return (degreGlobalCommu/m_communauteNoeud[p_numeroCommunaute].size());
}

// Calcule le degre interne/entrant d'un noeud
float GuimeraAmaral::degreIntCom(int p_numeroSommet, int p_numeroCommunaute, vector<int> degresInternes, vector<int> liensInternes){
    unsigned int posOut, posOutFin;
    float cpt = 0;
    if (p_numeroSommet==0)
        posOut = 0;
    else
        posOut = degresInternes[p_numeroSommet-1];
        posOutFin = degresInternes[p_numeroSommet];
    for (unsigned int i = posOut; i < posOutFin; i++){
        int tmp, tmpBis;
        tmpBis = liensInternes[i];
        //tmp = m_communauteNoeud[tmpBis];
        //if (tmp==p_numeroCommunaute) cpt++;
    }
}

// Calcule l'ecart type interne (?)
double GuimeraAmaral::ecartTypeInt(int p_numeroCommunaute){
    return sqrt(varianceInt(p_numeroCommunaute));
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double GuimeraAmaral::zScoreInt(int p_numeroSommet, int p_numeroCommunaute){
    vector <int> ecartTypeInterne;
    vector <int> degreInterneCommu;
    vector <double> degreMoyenInterneCommu;
    if (ecartTypeInterne[p_numeroCommunaute]==0)
       return 0;
    else
       return ((degreInterneCommu[p_numeroSommet]-degreMoyenInterneCommu[p_numeroCommunaute])/ecartTypeInterne[p_numeroCommunaute]);
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
