#include "cell.h"

#include <iostream>

double Cell::deriv()
{
    std::cout << m_lim.get( (m_u - cl->m_u)/m_delta, (cr->m_u - m_u)/m_delta ) << std::endl;
    return m_lim.get( (m_u - cl->m_u)/m_delta, (cr->m_u - m_u)/m_delta );
}

Cell::Cell()
{
    Cell (0);
}

Cell::Cell(double delta)
{
    m_delta = delta;
}

void Cell::set_delta(double delta)
{
    m_delta = delta;
}

Cell & Cell::operator =(const double & u)
{
    m_u = u;
    double du = deriv();

    ul = u - 0.5*m_delta*du;
    ur = u + 0.5*m_delta*du;
    fl = flux_l();
    fr = flux_r();
    al = a_l();
    ar = a_r();

    return *this;
}

// linear flux

double Cell::flux_l()
{
    return ul;
}

double Cell::flux_r()
{
    return ur;
}

double Cell::a_l()
{
    return 1;
}

double Cell::a_r()
{
    return 1;
}

std::ostream & operator<<(std::ostream & output, const Cell & c)
{
    output << "Je suis une cellule 1D\n";
    output << "Je mesure " << c.m_delta << "\n";
    output << "Je contiens les valeurs suivantes :" << "\n";
    output << "u = " << c.m_u << "\n" << "ul = " << c.ul << "\n" << "ur = " << c.ur << "\n";

    return output;
}
