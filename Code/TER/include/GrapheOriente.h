#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <omp.h>
#include "Graphe.h"

class GrapheOriente : public Graphe
{
    public:
        GrapheOriente(std::string const& p_nom);
        GrapheOriente(std::vector<int> const& p_degresCumulatifsSortants, std::vector<int> const& p_degresCumulatifsEntrants, std::vector<Arc> const& p_arcsSortants, std::vector<Arc> const& p_arcsEntrants, std::vector<double> const& p_poids);
        virtual ~GrapheOriente();
        virtual unsigned int size() const;
        virtual unsigned int nbArcs() const;
        virtual bool estOriente() const;
        virtual int getDegreBoucle(unsigned int const& p_numeroSommet) const;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const;
        virtual std::vector<Arc> getArcsSortants(unsigned int const& p_numeroSommet) const;
        virtual std::vector<Arc> getArcsEntrants(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsBoucle(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const;
        virtual double getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const;
    protected:
    private:
        std::vector<int> m_degresCumulatifsSortants;
        std::vector<int> m_degresCumulatifsEntrants;
        std::vector<Arc> m_arcsSortants;
        std::vector<Arc> m_arcsEntrants;
};

#endif // GRAPHEORIENTE_H
