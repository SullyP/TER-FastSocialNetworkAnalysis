#include "GuimeraAmaral.h"

// ecartTypeInterne[i] = ecartTypeInt(i);
// degreMoyenInterneCommu[i] = degreMoyenIntCom(i);
// degreInterneCommu[i] = degreIntCom(i);// Calcule la variance interne (?)

// Calcule la variance interne
double varianceInt(int commu){
    vector<int> degreInterneCommu;
    vector<int> degreMoyenInterneCommu;
    vector< vector<int> > communautes;
    double moyenne = degreMoyenInterneCommu[commu];
    double tmp = 0;
    double tmpBis = 0;
    double degreNoeud = 0;
    for (unsigned int i = 0; i < communautes[commu].size(); i++){
        degreNoeud = degreInterneCommu[communautes[commu][i]];
        tmpBis = degreNoeud - moyenne;
        tmp = tmpBis*tmpBis;
    }
    return (tmp/(double)communautes[commu].size());
}

// Calcule le degre moyen interne/entrant (?) d'une communaute
float degreMoyenIntCom(int commu, vector<int> degreInterneCommu, vector< vector<int> > communautes){
    long degreGlobalCommu = 0;
    for (unsigned int i = 0; i < communautes[commu].size(); i++){
         degreGlobalCommu += degreInterneCommu[communautes[commu][i]];
    }
    return (degreGlobalCommu/communautes[commu].size());
}

// Calcule le degre interne/entrant d'un noeud
float degreIntCom(int noeud, int commu, vector<int> degresInternes, vector<int> liensInternes, vector< vector<int> > mapCommunautes){
    unsigned int posOut, posOutFin;
    float cpt = 0;
    if (noeud==0)
        posOut = 0;
    else
        posOut = degresInternes[noeud-1];
        posOutFin = degresInternes[noeud];
    for (unsigned int i = posOut; i < posOutFin; i++){
        int tmp, tmpBis;
        tmpBis = liensInternes[i];
        //tmp = mapCommunautes[tmpBis];
        //if (tmp==commu) cpt++;
    }
}

// Calcule l'ecart type interne (?)
double ecartTypeInt(int commu){
    return sqrt(varianceInt(commu));
}

// Retourne le zscore d'une noeud en argument dans une communaute en argument pour un graphe g
double zScoreInt(int noeud, int commu){
    vector <int> ecartTypeInterne;
    vector <int> degreInterneCommu;
    vector <int> degreMoyenInterneCommu;
    if (ecartTypeInterne[commu]==0)
       return 0;
    else
       return ((degreInterneCommu[noeud]-degreMoyenInterneCommu[commu])/ecartTypeInterne[commu]);
}

// Retourne oui si le noeud est un hub, non sinon
bool estHub(int noeud, int commu, double seuil){
    return (zScoreInt(noeud, commu))>=seuil;
}

// Retourne le nombre de connexions entre deux communautes
int connexions(int commuA, int commuB){
    return 0;
}

// Retourne oui si le noeud est peripherique, non sinon
bool estPeriph(int noeud){
    return false;
}
