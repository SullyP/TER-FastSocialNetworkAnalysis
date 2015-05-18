#include <iostream>
#include <math.h>
#include "ParticipationExterne.h"

using namespace std;

ParticipationExterne::ParticipationExterne(Communaute const& p_communaute, int const& p_numeroSommet){
    const GrapheNonOriente* graphe = p_communaute.getGraphe();
    vector<int> listCommunaute = p_communaute.getNoeudCommunaute();
    vector<double> moyenne;
    vector<int> moyenneNoeud;
    vector<bool> visiteCommunaute;
    vector<int> participation;
    int cpt = 0;
    int nbCommunaute = 0;

    for (unsigned int i = 0; i < listCommunaute.size(); i++){
        if (listCommunaute[i] > nbCommunaute){
            nbCommunaute = listCommunaute[i];
        }
    }

    for(int i = 0; i <= nbCommunaute; i++){
        visiteCommunaute.push_back(false);
        moyenneNoeud.push_back(0);
    }

    for(int i = 0; i < 3; i++){
        participation.push_back(0);
    }

    for(unsigned int noeud = 0; noeud < listCommunaute.size(); noeud++){

        if (listCommunaute[noeud] == p_numeroSommet){
            moyenne.push_back(0);
            vector<Arc> voisins = graphe->getArcsSortants(noeud);
            for(unsigned int i = 0; i < voisins.size(); i++){
                if (listCommunaute[voisins[i].getNumeroSommet()] != listCommunaute[noeud]){

                    if (!visiteCommunaute[listCommunaute[voisins[i].getNumeroSommet()]]){
                        participation[0]++;
                        visiteCommunaute[listCommunaute[voisins[i].getNumeroSommet()]] = true;
                    }

                    moyenneNoeud[listCommunaute[voisins[i].getNumeroSommet()]]++;
                    participation[1]++;
                }
            }

            int comVisite = 0;
            int total = 0;
            for (unsigned int i = 0; i < moyenneNoeud.size(); i++){
                if (moyenneNoeud[i] != 0){
                    comVisite++;
                    total += moyenneNoeud[i];
                }
            }

            moyenne[cpt] = total/comVisite;

            for(int i = 0; i <= nbCommunaute; i++){
                moyenneNoeud.push_back(0);
            }
            cpt++;

        }
    }

    double hetero = 0;
    double moyenneTotal = 0;

    for (unsigned int i = 0; i < moyenne.size(); i++){
        hetero += moyenne[i]*moyenne[i];
        moyenneTotal++;
    }

    hetero /= moyenneTotal;

    participation[2] = sqrt(hetero);

    participation[1] /= cpt;

    m_diversite = participation[0];
    m_intensite = participation[1];
    m_heterogeneite = participation[2];
}

ParticipationExterne::~ParticipationExterne(){
    //dtor
}

int ParticipationExterne::getDiversite() const{
    return m_diversite;
}
int ParticipationExterne::getIntensite() const{
    return m_intensite;
}
int ParticipationExterne::getHeterogeneite() const{
    return m_heterogeneite;
}
