#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include <Graphe.h>

class GrapheOriente : public Graphe
{
    public:
        GrapheOriente();
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
