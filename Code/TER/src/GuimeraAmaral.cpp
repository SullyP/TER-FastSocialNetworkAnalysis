#include "GuimeraAmaral.h"

// Retourne le zscore d'une noeud en argument dans une communaute en argument
double zScoreIn(int noeud, int commu){
    double zsi = Graph::z_score_in(noeud, commu);
    return zsi;
}

// Retourne la participation externe d'un noeud en argument
double participationExterne(int noeud){
    double pext = Graph::participation_out(noeud);
    return pext;
}

// Retourne oui si le noeud est connecté, non sinon
bool estConnect(int noeud){
    return false;
}

// Retourne oui si le noeud est un hub, non sinon
bool estHub(int noeud, int commu, double seuil){
    return (Graph::z_score_out(noeud,commu))>=seuil;
}

// Retourne oui si le noeud est peripherique, non sinon
bool estPeriph(int noeud){
    return false;
}
