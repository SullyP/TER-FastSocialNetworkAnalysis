#ifndef GRAPHENONORIENTE_H
#define GRAPHENONORIENTE_H

#include "Graphe.h"
#include "GrapheOriente.h"

class GrapheNonOriente : public Graphe
{
    public:
        GrapheNonOriente(std::vector<int> const& p_degresCumulatifs, std::vector<Arc> const& p_arcs, std::vector<double> const& p_poids, unsigned int p_nbArcs);
        GrapheNonOriente(GrapheOriente const& p_graphe);
        virtual ~GrapheNonOriente();
        virtual unsigned int size() const;
        virtual unsigned int nbArcs() const;
        virtual int getDegreBoucle(unsigned int const& p_numeroSommet) const;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const;
        virtual std::vector<Arc> getArcsSortants(unsigned int const& p_numeroSommet) const;
        virtual std::vector<Arc> getArcsEntrants(unsigned int const& p_numeroSommet) const;
        std::vector<Arc> getArcs(unsigned int const& p_numeroSommet) const;
        int getDegre(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsBoucle(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const;
        double getSommePoidsArcs(unsigned int const& p_numeroSommet) const;
    protected:
    private:
        std::vector<int> m_degresCumulatifs;
        std::vector<Arc> m_arcs;
        unsigned int m_nbArcs;
};

#endif // GRAPHENONORIENTE_H
