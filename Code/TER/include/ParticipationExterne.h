#include "Communaute.h"
#include "GrapheNonOriente.h"

#ifndef EXTERNE_H
#define EXTERNE_H

class ParticipationExterne
{
    public:
        ParticipationExterne(Communaute const& p_communaute, int const& p_numeroSommet);
        virtual ~ParticipationExterne();
        int getDiversite() const;
        int getIntensite() const;
        int getHeterogeneite() const;
    protected:
    private:
        int m_diversite, m_intensite, m_heterogeneite;
};

#endif
