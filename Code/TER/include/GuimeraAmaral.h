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
        GuimeraAmaral(Communaute const& p_communaute);
        double varianceInt(int p_numeroCommunaute);
        double degreMoyenIntCom(int p_numeroCommunaute);
        int degreIntCom(int noeud, int p_numeroCommunaute);
        double ecartTypeInt(int p_numeroCommunaute);
        double zScoreInt(int noeud, int p_numeroCommunaute);
        bool estHub(int noeud, int p_numeroCommunaute);
        bool estConnect(int noeud);
        bool estPeriph(int noeud);
        int connexions(int p_numeroCommunauteA, int p_numeroCommunauteB);
    private:
        std::vector<int> m_noeudCommunaute; // Pour chaque noeud, la communaut� � laquelle il appartient
        std::vector< std::vector<int> > m_communauteNoeud; //Pour chaque communaut�, la liste des noeuds lui appartenant
        std::vector<int> m_degreInterneCommunaute; //Degr� interne de chaque noeud pour sa communaut�
        std::vector<double> m_degreMoyenInterneCommunaute; //Pour chaque communaut�, son degr� moyen interne
        std::vector<double> m_ecartTypeInterneCommunaute; //Pour chaque communaut�, son �cart type interne
        const GrapheNonOriente* m_graphe;
};

#endif // GUIMERAAMARAL_H
