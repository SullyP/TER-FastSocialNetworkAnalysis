#ifndef GUIMERAAMARAL_H
#define GUIMERAAMARAL_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include"Communaute.h"

using namespace std;

class GuimeraAmaral {
    public:
        GuimeraAmaral(std::vector<int> const& p_noeudCommunaute, std::vector< std::vector<int> > const& p_communauteNoeud, const Graphe* p_graphe);
        double varianceEntrante(int p_numeroCommunaute);
        double varianceSortante(int p_numeroCommunaute);
        double zScoreEntrantCommunaute(int noeud, int p_numeroCommunaute);
        double zScoreSortantCommunaute(int noeud, int p_numeroCommunaute);
        bool estHub(int noeud, int p_numeroCommunaute);
        bool estConnect(int noeud);
        bool estPeriph(int noeud);
        int connexions(int p_numeroCommunauteA, int p_numeroCommunauteB);
        //Getters
        vector<int> getNoeudCommunaute() const;
        vector< vector<int> > getCommunauteNoeud() const;
        vector<int> getDegreEntrantCommunaute() const;
        vector<double> getDegreMoyenEntrantCommunaute() const;
        vector<double> getEcartTypeEntrantCommunaute() const;
        vector<int> getDegreSortantCommunaute() const;
        vector<double> getDegreMoyenSortantCommunaute() const;
        vector<double> getEcartTypeSortantCommunaute() const;
        const Graphe* getGraphe() const;
    private:
        //Fonctions de calculs pour le constructeur
        double degreMoyenEntrantCommunaute(int p_numeroCommunaute);
        int degreEntrantCommunaute(int noeud, int p_numeroCommunaute);
        double ecartTypeEntrantCommunaute(int p_numeroCommunaute);
        double degreMoyenSortantCommunaute(int p_numeroCommunaute);
        int degreSortantCommunaute(int noeud, int p_numeroCommunaute);
        double ecartTypeSortantCommunaute(int p_numeroCommunaute);

        std::vector<int> m_noeudCommunaute; // Pour chaque noeud, la communauté à laquelle il appartient
        std::vector< std::vector<int> > m_communauteNoeud; //Pour chaque communauté, la liste des noeuds lui appartenant
        std::vector<int> m_degreEntrantCommunaute; //Degré interne de chaque noeud pour sa communauté
        std::vector<double> m_degreMoyenEntrantCommunaute; //Pour chaque communauté, son degré moyen interne
        std::vector<double> m_ecartTypeEntrantCommunaute; //Pour chaque communauté, son écart type interne
        std::vector<int> m_degreSortantCommunaute; //Degré sortant de chaque noeud pour sa communauté
        std::vector<double> m_degreMoyenSortantCommunaute; //Pour chaque communauté, son degré moyen sortant
        std::vector<double> m_ecartTypeSortantCommunaute; //Pour chaque communauté, son écart type sortant
        const Graphe* m_graphe;
};

#endif // GUIMERAAMARAL_H
