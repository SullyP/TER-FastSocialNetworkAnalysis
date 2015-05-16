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
        float degreMoyenIntCom(int p_numeroCommunaute, vector<int> degreInterneCommu);
        float degreIntCom(int noeud, int p_numeroCommunaute, vector<int> degresInternes, vector<int> liensInternes);
        double ecartTypeInt(int p_numeroCommunaute);
        double zScoreInt(int noeud, int p_numeroCommunaute);
        bool estHub(int noeud, int p_numeroCommunaute);
        bool estConnect(int noeud);
        bool estPeriph(int noeud);
        int connexions(int p_numeroCommunauteA, int p_numeroCommunauteB);
    private:
        std::vector<int> m_noeudCommunaute; // Pour chaque noeud, la communauté à laquelle il appartient
        std::vector< std::vector<int> > m_communauteNoeud; //Pour chaque communauté, la liste des noeuds lui appartenant
        const GrapheNonOriente* m_graphe;
};

#endif // GUIMERAAMARAL_H
