#include "GuimeraAmaral.h"

// Retourne le zscore d'une noeud en argument dans une communaute en argument
double zScoreIn(Graph g, int noeud, int commu){
    double zsi = g.z_score_in(noeud, commu);
    return 0;
}

// Retourne la participation externe d'un noeud en argument
double participationExterne(Graph g,int noeud){
    double pext = g.participation_out(noeud);
    return pext;
}

// Retourne oui si le noeud est connecté, non sinon
bool estConnect(int noeud){
    return false;
}

// Retourne oui si le noeud est un hub, non sinon
bool estHub(Graph g,int noeud, int commu, double seuil){
    return (g.z_score_out(noeud,commu))>=seuil;
}

// Retourne oui si le noeud est peripherique, non sinon
bool estPeriph(int noeud){
    return false;
}
