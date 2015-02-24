#include <vector>

#ifndef GRAPHE_H
#define GRAPHE_H


class Graphe
{
    public:
        virtual ~Graphe();
        int getPoids(unsigned int const& p_numeroSommet) const;
        //Methodes non-définies dans cette classe mais dans les classes filles (héritées)
        virtual unsigned int size() const = 0;
        virtual int getDegreSortant(unsigned int const& p_numeroSommet) const = 0;
        virtual int getDegreEntrant(unsigned int const& p_numeroSommet) const = 0;
        virtual std::vector<int> getArcsSortants(unsigned int const& p_numeroSommet) const = 0;
        virtual std::vector<int> getArcsEntrants(unsigned int const& p_numeroSommet) const = 0;
    protected:
        std::vector<int> m_poids;
    private:
};

#endif // GRAPHE_H
