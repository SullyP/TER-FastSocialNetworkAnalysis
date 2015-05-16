#ifndef COMMUNAUTE_H
#define COMMUNAUTE_H

#include"GrapheNonOriente.h"
#include <cstdlib>

class Communaute
{
    public:
        Communaute(const GrapheNonOriente* p_graphe, int const& p_nbPasses, double const& p_minModularite, std::vector<int> const& p_noeudCommunaute = std::vector<int>());
        virtual ~Communaute();
        double modularite() const;
        // Effectue une étape de l'algorithme de Louvain (calcul de communauté),
        // renvoye vrai si au moins un noeud a changé de communauté
        bool effectuerUneEtape();
        // Renvoye la partition, pour chaque noeud, sa communauté.
        std::vector<int> getNoeudCommunaute() const;
        // Renvoye la partition, pour chaque communauté, ses noeuds .
        std::vector< std::vector<int> > getCommunauteNoeud() const;
        // Renvoye le graphe avant partition
        const GrapheNonOriente* getGraphe() const;
        // Renvoye le graphe après partition
        GrapheNonOriente* getGrapheCommunaute() const;
    protected:
    private:
        // Supprime le sommet de sa communauté actuel avec laquelle il a poidsArcsNoeudCommunaute liens pondérés
        inline void supprimeCommunaute(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute);
        // Ajoute le sommet à la communauté avec laquelle il a poidsArcsNoeudCommunaute liens pondérés
        inline void ajouteCommunaute(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute);
        // Calcul le gain de modularité
        inline double modulariteGain(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute) const;

        const GrapheNonOriente* m_graphe;
        int m_nbPasses; // Nombre de passes à éffectuer
        double m_minModularite; // Modularité minimum en desous de laquelle le gain n'est plus assez élevé pour fusionner des communautés/noeuds
        std::vector<int> m_noeudCommunaute; // Pour chaque noeud, la communauté à laquelle il appartient
        std::vector< std::vector<int> > m_communauteNoeud; //Pour chaque communauté, la liste des noeuds lui appartenant
        std::vector<double> m_in; // Pour chaque communauté, la somme des poids des arcs internes
        std::vector<double> m_tot; // Pour chaque communauté, la somme des poids des arcs entrants (depuis une autre communauté)

        void calculVoisinageCommunaute(unsigned int const& p_numeroSommet);
        std::vector<double> m_voisinagePoids;
        std::vector<unsigned int> m_voisinageIndice;
        unsigned int m_voisinageBorneMax;
};

inline void Communaute::supprimeCommunaute(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute){
    assert(p_numeroSommet < m_graphe->size());

    m_tot[p_communaute] -= m_graphe->getSommePoidsArcsSortants(p_numeroSommet);
    m_in[p_communaute]  -= 2*p_poidsArcsNoeudCommunaute + m_graphe->getDegreBoucle(p_numeroSommet);
    m_noeudCommunaute[p_numeroSommet]  = -1;
}

inline void Communaute::ajouteCommunaute(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute){
    assert(p_numeroSommet < m_graphe->size());

    m_tot[p_communaute] += m_graphe->getSommePoidsArcsSortants(p_numeroSommet);
    m_in[p_communaute]  += 2*p_poidsArcsNoeudCommunaute + m_graphe->getDegreBoucle(p_numeroSommet);
    m_noeudCommunaute[p_numeroSommet] = p_communaute;
}

inline double Communaute::modulariteGain(unsigned int const& p_numeroSommet, int const& p_communaute, double const& p_poidsArcsNoeudCommunaute) const{
    assert(p_numeroSommet < m_graphe->size());

    return (p_poidsArcsNoeudCommunaute - m_tot[p_communaute]*m_graphe->getSommePoidsArcsSortants(p_numeroSommet)/m_graphe->getPoidsTotalArcs());
}

#endif // COMMUNAUTE_H
