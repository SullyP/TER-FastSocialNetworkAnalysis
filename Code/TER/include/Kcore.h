#ifndef KCORE_H
#define KCORE_H
#include "GrapheNonOriente.h"

using namespace std;

class Kcore
{
    public:
        Kcore(GrapheNonOriente* graphe, int k);
        vector<int> getTabDegre() const;
        GrapheNonOriente* getGrapheKcore() const;
    private:
        bool supK (std::vector<int> tabdegre, int k);
        std::vector<int> m_tabDegre;
        GrapheNonOriente* m_grapheKcore;
};

#endif // KCORE_H
