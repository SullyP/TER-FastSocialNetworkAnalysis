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
        int m_nbPasses; //Nombre de passes � �ffectuer
        double m_minModularite; //Modularit� minimum en desous de laquelle le gain n'est plus assez �lev� pour fusionner des communaut�s/noeuds
        std::vector<int> m_noeudCommunaute; //Pour chaque noeud, la communaut� � laquelle il appartient
        std::vector<double> m_in; //Pour chaque communaut�, la somme des poids des arcs internes
        std::vector<double> m_tot; //Pour chaque communaut�, la somme des poids des arcs entrants (depuis une autre communaut�)
};

#endif // COMMUNAUTE_H
