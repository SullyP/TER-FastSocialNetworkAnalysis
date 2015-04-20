#include "Arc.h"

Arc::Arc(double const& p_poids, unsigned int const& p_numeroSommet){
    m_poids = p_poids;
    m_numeroSommet = p_numeroSommet;
}

Arc::~Arc()
{
    //dtor
}
