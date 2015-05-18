#ifndef KCORE_H
#define KCORE_H
#include "GrapheNonOriente.h"

using namespace std;

class Kcore
{
    public:
        std::vector<int> kcore(GrapheNonOriente* graphe, int k);
        bool supK (std::vector<int> tabdegre, int k);
    //private:
};

#endif // KCORE_H
