#ifndef ARC_H
#define ARC_H


class Arc
{
    public:
        Arc(double const& p_poids, unsigned int const& p_numeroSommet);
        virtual ~Arc();
        double getPoids() const { return m_poids; }
        unsigned int getNumeroSommet() const { return m_numeroSommet; }
    protected:
    private:
        double m_poids;
        unsigned int m_numeroSommet;
};

#endif // ARC_H
