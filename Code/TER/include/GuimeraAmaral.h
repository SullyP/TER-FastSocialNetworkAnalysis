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

enum Connectivite { TRESFAIBLE = -1, FAIBLE = 0, FORT = 1, TRESFORT = 2};

class GuimeraAmaral {
    public:
        GuimeraAmaral(std::vector<int> const& p_noeudCommunaute, std::vector< std::vector<int> > const& p_communauteNoeud, const Graphe* p_graphe);
        double varianceEntrante(int const& p_numeroCommunaute) const;
        double varianceSortante(int const& p_numeroCommunaute) const;
        double zScoreEntrantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute) const;
        double zScoreSortantCommunaute(int const& p_numeroSommet, int const& p_numeroCommunaute) const;
        bool estHub(int const& p_numeroSommet, int const& p_numeroCommunaute) const;
        double participationExterne(int const& p_numeroSommet) const;
        double participationInterne(int const& p_numeroSommet) const;
        bool estPeripherique(int const& p_numeroSommet) const;
        bool estUltraPeripherique(int const& p_numeroSommet) const;
        Connectivite connectiviteNoeud(int const& p_numeroSommet) const;
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
        double degreMoyenEntrantCommunaute(int const& p_numeroCommunaute)  const;
        int degreEntrantCommunaute(int const& noeud, int const& p_numeroCommunaute)  const;
        double ecartTypeEntrantCommunaute(int const& p_numeroCommunaute)  const;
        double degreMoyenSortantCommunaute(int const& p_numeroCommunaute)  const;
        int degreSortantCommunaute(int const& noeud, int const& p_numeroCommunaute)  const;
        double ecartTypeSortantCommunaute(int const& p_numeroCommunaute)  const;

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
