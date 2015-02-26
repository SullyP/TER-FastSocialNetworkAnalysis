#include "IndiceEnsembliste.h"

IndiceEnsembliste::IndiceEnsembliste(std::vector<int> p_ensembleA, std::vector<int> p_ensembleB){
    m_tailleEnsembleA = p_ensembleA.size();
    m_tailleEnsembleB = p_ensembleB.size();
    std::vector<int> intersection;

    sort(p_ensembleA.begin(), p_ensembleA.end());
    sort(p_ensembleB.begin(), p_ensembleB.end());

    std::set_intersection(p_ensembleA.begin(),p_ensembleA.end(),p_ensembleB.begin(),p_ensembleB.end(),back_inserter(intersection));

    m_tailleIntersection = intersection.size();
    m_tailleUnion = m_tailleEnsembleA + m_tailleEnsembleB - m_tailleIntersection;
}

IndiceEnsembliste::~IndiceEnsembliste(){
    //dtor
}

double IndiceEnsembliste::jaccard() const{
    return (double)m_tailleIntersection / (double)m_tailleUnion;
}

double IndiceEnsembliste::overlapIndex() const{
    return (double)m_tailleIntersection / (double)std::min(m_tailleEnsembleA, m_tailleEnsembleB);
}
