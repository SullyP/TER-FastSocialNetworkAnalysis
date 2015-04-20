#ifndef COMMUNAUTE_H
#define COMMUNAUTE_H

#include"Graphe.h"

class Communaute
{
    public:
        Communaute(const Graphe* p_graphe, int const& p_nbPasses, double const& p_minModularite);
        virtual ~Communaute();
        double modularite() const;
    protected:
    private:
        const Graphe* m_graphe;
        int m_nbPasses; //Nombre de passes à éffectuer
        double m_minModularite; //Modularité minimum en desous de laquelle le gain n'est plus assez élevé pour fusionner des communautés/noeuds
        std::vector<int> m_noeudCommunaute; //Pour chaque noeud, la communauté à laquelle il appartient
        std::vector<double> m_in; //Pour chaque communauté, la somme des poids des arcs internes
        std::vector<double> m_tot; //Pour chaque communauté, la somme des poids des arcs entrants (depuis une autre communauté)
};

#endif // COMMUNAUTE_H
