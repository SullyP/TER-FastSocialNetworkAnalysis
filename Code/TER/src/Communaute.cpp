#include "Communaute.h"'

Communaute::Communaute(const Graphe* p_graphe, int const& p_nbPasses, double const& p_minModularite){
    m_graphe = p_graphe;
    m_nbPasses = p_nbPasses;
    m_minModularite = p_minModularite;

    for (unsigned int numeroSommet=0 ; numeroSommet < m_graphe->size() ; numeroSommet++) {
        m_noeudCommunaute.push_back(numeroSommet);
        m_in.push_back(m_graphe->getSommePoidsBoucle(numeroSommet));
        m_tot.push_back(m_graphe->getSommePoidsArcsEntrants(numeroSommet));
    }
}

Communaute::~Communaute()
{
    //dtor
}

double Communaute::modularite() const{
    double mod  = 0.;
    double m2 = m_graphe->getPoidsTotalArcs();

    for (int i=0 ; i < m_graphe->size() ; i++) {
        if (m_tot[i]>0){
          mod += (double)m_in[i]/m2 - ((double)m_tot[i]/m2)*((double)m_tot[i]/m2);
        }
    }

    return mod;
}
