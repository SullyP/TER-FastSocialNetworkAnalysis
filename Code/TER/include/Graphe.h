#include <vector>
#include <queue>
#include "Arc.h"

#ifndef GRAPHE_H
#define GRAPHE_H


class Graphe
{
    public:
        virtual ~Graphe();
        double getPoids(unsigned int const& p_numeroSommet) const;
        std::vector<bool> breadthFirstSearch(unsigned int const& p_numeroSommet, std::vector<int> const& p_sommetsANePasPrendreEnCompte = std::vector<int>()) const;
        //Methodes non-définies dans cette classe mais dans les classes filles (héritées)
        virtual unsigned int size() const = 0;
        virtual unsigned int nbArcs() const = 0;
        virtual int getDegreBoucle(unsigned int const& p_numeroSommet) const = 0;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const = 0;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const = 0;
        virtual std::vector<Arc> getArcsSortants(unsigned int const& p_numeroSommet) const = 0;
        virtual std::vector<Arc> getArcsEntrants(unsigned int const& p_numeroSommet) const = 0;
        virtual int getSommePoidsBoucle(unsigned int const& p_numeroSommet) const = 0;
        virtual int getSommePoidsArcsEntrants(unsigned int const& p_numeroSommet) const = 0;
        virtual int getSommePoidsArcsSortants(unsigned int const& p_numeroSommet) const = 0;
    protected:
        std::vector<double> m_poids;
    private:
};

#endif // GRAPHE_H
