#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include <omp.h>
#include "Graphe.h"
#include "GrapheNonOriente.h"

class GrapheOriente : public Graphe
{
    public:
        GrapheOriente(std::vector<int> const& p_degresCumulatifsSortants, std::vector<int> const& p_degresCumulatifsEntrants, std::vector<int> const& p_arcsSortants, std::vector<int> const& p_arcsEntrants, std::vector<int> const& p_poids);
        GrapheNonOriente* convertToGrapheNonOriente() const;
        virtual ~GrapheOriente();
        virtual unsigned int size() const;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const;
        virtual std::vector<int> getArcsSortants(unsigned int const& p_numeroSommet) const;
        virtual std::vector<int> getArcsEntrants(unsigned int const& p_numeroSommet) const;
    protected:
    private:
        std::vector<int> m_degresCumulatifsSortants;
        std::vector<int> m_degresCumulatifsEntrants;
        std::vector<int> m_arcsSortants;
        std::vector<int> m_arcsEntrants;
};

#endif // GRAPHEORIENTE_H
