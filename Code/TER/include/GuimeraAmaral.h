#ifndef GUIMERAAMARAL_H
#define GUIMERAAMARAL_H

#include "GrapheBinary.h"

using namespace std;

class GuimeraAmaral {
  public:
    double zscorein(int node, int commu);
    double participationExterne(int noeud);
    bool estHub(int noeud, int commu, double seuil);
    bool estConnect(int noeud);
    bool estPeriph(int noeud);
  private:
    unsigned int node = 0;
    int comm = 0;
    double seuil=2.5;
};

#endif // GUIMERAAMARAL_H
