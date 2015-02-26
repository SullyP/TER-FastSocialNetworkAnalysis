#ifndef INDICEENSEMBLISTE_H
#define INDICEENSEMBLISTE_H

#include <vector>
#include <algorithm>
#include <iterator>

class IndiceEnsembliste
{
    public:
        IndiceEnsembliste(std::vector<int> p_ensembleA, std::vector<int> p_ensembleB);
        virtual ~IndiceEnsembliste();
        double jaccard() const;
        double overlapIndex() const;
    protected:
    private:
        int m_tailleEnsembleA, m_tailleEnsembleB, m_tailleIntersection, m_tailleUnion;
};

#endif // INDICEENSEMBLISTE_H
