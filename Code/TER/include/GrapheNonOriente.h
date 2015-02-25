#ifndef GRAPHENONORIENTE_H
#define GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe
{
    public:
        GrapheNonOriente(std::vector<int> const& p_degresCumulatifs, std::vector<int> const& p_arcs, std::vector<int> const& p_poids);
        virtual ~GrapheNonOriente();
        virtual unsigned int size() const;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const;
        virtual std::vector<int> getArcsSortants(unsigned int const& p_numeroSommet) const;
        virtual std::vector<int> getArcsEntrants(unsigned int const& p_numeroSommet) const;
        std::vector<int> getArcs(unsigned int const& p_numeroSommet) const;
        int getDegre(unsigned int const& p_numeroSommet) const;
    protected:
    private:
        std::vector<int> m_degresCumulatifs;
        std::vector<int> m_arcs;
};

#endif // GRAPHENONORIENTE_H
