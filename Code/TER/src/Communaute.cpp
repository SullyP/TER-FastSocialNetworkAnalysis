#include "Communaute.h"

Communaute::Communaute(const GrapheNonOriente* p_graphe, int const& p_nbPasses, double const& p_minModularite, std::vector<int> const& p_noeudCommunaute){
    m_graphe = p_graphe;
    m_nbPasses = p_nbPasses;
    m_minModularite = p_minModularite;

    m_voisinagePoids.resize(m_graphe->size(), -1);
    m_voisinageIndice.resize(m_graphe->size());
    m_voisinageBorneMax = 0;

    for (unsigned int numeroSommet=0 ; numeroSommet < m_graphe->size() ; numeroSommet++) {
        m_noeudCommunaute.push_back(numeroSommet);
        m_in.push_back(m_graphe->getSommePoidsBoucle(numeroSommet));
        m_tot.push_back(m_graphe->getSommePoidsArcsEntrants(numeroSommet));
    }

    //Si la partition est initialisée
    if(p_noeudCommunaute.size() == m_graphe->size()){
        // On vérifie que la communautée pour chaque noeud est bien optimale, avant de l'ajouter
        for(unsigned int numeroSommet = 0; numeroSommet < p_noeudCommunaute.size(); numeroSommet++){
            int oldComm = m_noeudCommunaute[numeroSommet];
            calculVoisinageCommunaute(numeroSommet);

            supprimeCommunaute(numeroSommet, oldComm, m_voisinagePoids[oldComm]);

            for(unsigned int i = 0; i < m_voisinageBorneMax; i++){
                int meilleurComm = m_voisinageIndice[i];
                double meilleurPoidsArcs  = m_voisinagePoids[m_voisinageIndice[i]];
                if (meilleurComm == p_noeudCommunaute[numeroSommet]){
                    ajouteCommunaute(numeroSommet, meilleurComm, meilleurPoidsArcs);
                    break;
                }else if(i == m_voisinageBorneMax){
                    ajouteCommunaute(numeroSommet, p_noeudCommunaute[numeroSommet], 0);
                }
            }
        }
    }
}

Communaute::~Communaute()
{
    //dtor
}

double Communaute::modularite() const{
    double mod  = 0.;
    double m2 = m_graphe->getPoidsTotalArcs();

    for (unsigned int i=0 ; i < m_graphe->size() ; i++) {
        if (m_tot[i]>0){
          mod += (double)m_in[i]/m2 - ((double)m_tot[i]/m2)*((double)m_tot[i]/m2);
        }
    }

    return mod;
}

bool Communaute::effectuerUneEtape(){
    bool deplacement = false;
    double newModularite = modularite();
    double curModularite = newModularite;
    int nbTourDeBoucle = 0;
    int nbDeplacement;

    //On créer un ordre aléatoire pour les sommets
    std::vector<int> random_order(m_graphe->size());
    for (unsigned int i=0 ; i < m_graphe->size() ; i++){
        random_order[i]=i;
    }
    for (unsigned int i=0 ; i  < m_graphe->size()-1 ; i++) {
        int rand_pos = rand()%(m_graphe->size()-i)+i;
        int tmp      = random_order[i];
        random_order[i] = random_order[rand_pos];
        random_order[rand_pos] = tmp;
    }

    //Tant que la modularité est améliorée (amelioration > m_minModularite)
    //ou tant que le nombre de tour de boucle maximal n'est pas atteint
    do{
        nbDeplacement = 0;
        curModularite = newModularite;
        nbTourDeBoucle++;

        // Pour chaque sommet, le supprimer de sa communauté et l'ajouter dans la meilleure communauté
        for (unsigned int indice=0 ; indice < m_graphe->size() ; indice++) {
            unsigned int numeroSommet = random_order[indice];
            int communaute = m_noeudCommunaute[numeroSommet];

            calculVoisinageCommunaute(numeroSommet);
            supprimeCommunaute(numeroSommet, communaute, m_voisinagePoids[communaute]);

            int meilleurCommunaute = communaute;
            double meilleurPoidsArcs = 0.;
            double meilleurGain = 0.;
            for (unsigned int numeroSommetVoisin=0 ; numeroSommetVoisin < m_voisinageBorneMax ; numeroSommetVoisin++) {
                double gain = modulariteGain(numeroSommet, m_voisinageIndice[numeroSommetVoisin], m_voisinagePoids[m_voisinageIndice[numeroSommetVoisin]]);
                if (gain > meilleurGain) {
                    meilleurCommunaute = m_voisinageIndice[numeroSommetVoisin];
                    meilleurPoidsArcs = m_voisinagePoids[m_voisinageIndice[numeroSommetVoisin]];
                    meilleurGain = gain;
                }
            }

            ajouteCommunaute(numeroSommet, meilleurCommunaute, meilleurPoidsArcs);

            if (meilleurCommunaute != communaute){
                nbDeplacement++;
            }
        }

        newModularite = modularite();
        if (nbDeplacement>0){
            deplacement=true;
        }

    } while (nbDeplacement>0 && newModularite-curModularite>m_minModularite);

    //On calcule noeudCommunaute
    for(unsigned numeroSommet=0; numeroSommet < m_noeudCommunaute.size(); numeroSommet++){
        if((unsigned)m_noeudCommunaute[numeroSommet] >= m_communauteNoeud.size()){
            //Si la communauté n'est pas dans la liste, on aggrandit la liste
            m_communauteNoeud.resize(m_noeudCommunaute[numeroSommet]+1);
        }
        (m_communauteNoeud[m_noeudCommunaute[numeroSommet]]).push_back(numeroSommet);
    }

    return deplacement;
}

std::vector<int> Communaute::getNoeudCommunaute() const{
    return m_noeudCommunaute;
}

std::vector< std::vector<int> > Communaute::getCommunauteNoeud() const{
    return m_communauteNoeud;
}

const GrapheNonOriente* Communaute::getGraphe() const{
    return m_graphe;
}

GrapheNonOriente* Communaute::getGrapheCommunaute() const{
    //Variables pour la construction du graphe
    std::vector<int> degresCumulatifs;
    std::vector<Arc> arcs;
    std::vector<double> poids;
    unsigned int nbArcs = 0;

    //Variables pour le calcul des communautés
    std::vector<int> communautes(m_graphe->size(), -1);
    unsigned int nbCommunautes = 0;

    for(unsigned int numeroSommet = 0 ; numeroSommet < m_graphe->size(); numeroSommet++){
        //On compte le nombre de sommet pour chaque communauté
        communautes[m_noeudCommunaute[numeroSommet]]++;
    }
    for(unsigned int indice = 0; indice < m_graphe->size(); indice++){
        if(communautes[indice] != 1){
            //S'il y a au moins un sommet dans cette communauté, on lui donne un nouveau numéro
            //Afin d'avoir des communautés allant de 0 jusqu'à nbCommunautes
            communautes[indice] = nbCommunautes++;
        }
    }

    std::vector< std::vector<int> > communauteNoeud(nbCommunautes);
    //On cherche à obtenir la liste des noeuds de chaque communaute
    for(unsigned int numeroSommet = 0 ; numeroSommet < m_graphe->size(); numeroSommet++){
        communauteNoeud[communautes[m_noeudCommunaute[numeroSommet]]].push_back(numeroSommet);
    }

    //On peut donc désormais calculer les degrés cumulatifs du graphe
    for(unsigned int communaute = 0; communaute < nbCommunautes; communaute++){
        if(communaute == 0){
            degresCumulatifs.push_back(communauteNoeud[communaute].size());
        }else{
            degresCumulatifs.push_back(communauteNoeud[communaute].size() + degresCumulatifs[communaute-1]);
        }
    }

    //On cherche à calculer les arcs pour chaque communaute
    for(unsigned int communaute = 0; communaute < nbCommunautes; communaute++){
        std::vector<double> poidsArcs(nbCommunautes, 0.);

        //Pour chaque noeud de la communaute on somme le poids des arcs avec les autres communautés
        for(unsigned int indice = 0; indice < communauteNoeud[communaute].size(); indice++){
            unsigned int numeroSommet = communauteNoeud[communaute][indice];
            std::vector<Arc> voisins = m_graphe->getArcs(numeroSommet);

            for(unsigned int indice2 = 0; indice2 < voisins.size(); indice2++){
                unsigned int comm = m_noeudCommunaute[voisins[indice2].getNumeroSommet()];
                if(comm != communaute){
                    //Si c'est un arc avec une autre communauté, on somme le poids de cet arc
                    poidsArcs[comm] += voisins[indice2].getPoids();
                }
            }
        }

        for(unsigned int comm = 0; comm < poidsArcs.size(); comm++){
            //On ajoute les arcs dans la liste des arcs du graphe
            if(poidsArcs[comm] > 0){
                arcs.push_back(Arc(poidsArcs[comm],comm));
                if(!(comm > communaute)){
                   // Si la communauté vers lequel pointe l'arc est plus grand ou égale que la communauté de départ de l'arc
                   // On compte cet arc en plus, car cet arc n'a pas été compter jusqu'à maintenant.
                   nbArcs++;
                }
            }
        }
    }


    return new GrapheNonOriente(degresCumulatifs, arcs, poids, nbArcs);
}

void Communaute::calculVoisinageCommunaute(unsigned int const& p_numeroSommet){
    // Re-initialisation des données précédentes
    for (unsigned int indice = 0 ; indice < m_voisinageBorneMax ; indice++){
        m_voisinagePoids[ m_voisinageIndice[indice] ] = -1;
    }
    m_voisinageBorneMax = 0;

    std::vector<Arc> voisins = m_graphe->getArcs(p_numeroSommet);

    m_voisinageIndice[0] = m_noeudCommunaute[p_numeroSommet];
    m_voisinagePoids[ m_voisinageIndice[0] ] = 0;
    m_voisinageBorneMax = 1;

    for (unsigned int indice = 0 ; indice < voisins.size() ; indice++) {
        unsigned int voisin = voisins[indice].getNumeroSommet();
        unsigned int voisinCommunaute = m_noeudCommunaute[voisin];

        if (voisin != p_numeroSommet) {
            if (m_voisinagePoids[voisinCommunaute] == -1) {
                m_voisinagePoids[voisinCommunaute] = 0.;
                m_voisinageIndice[m_voisinageBorneMax++] = voisinCommunaute;
            }
            m_voisinagePoids[voisinCommunaute] += voisins[indice].getPoids();
        }
    }
}
