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

using namespace std;

class GuimeraAmaral {
  public:
    double varianceInt(int commu);
    float degreMoyenIntCom(int commu);
    float degreIntCom(int noeud, int commu);
    double ecartTypeInt(int commu);
    double zScoreInt(int noeud, int commu);
    bool estHub(int noeud, int commu, double seuil);
    bool estConnect(int noeud);
    bool estPeriph(int noeud);
  private:
    unsigned int node = 0;
    int comm = 0;
    double seuil=2.5;
};

#endif // GUIMERAAMARAL_H
