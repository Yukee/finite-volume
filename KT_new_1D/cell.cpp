#include "cell.h"

double Cell::deriv()
{
    return m_lim.get( (u - cl->u)/m_delta, (cr->u - u)/m_delta );
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

void Cell::evolve(const double dt)
{
    update(u);

    // KT scheme
    double flux = 0.5*(fr + cr->fl) - 0.5*std::max(fabs(ar), fabs(cr->al))*(ur - cr->ul)
            - 0.5*(fl + cl->fr) + 0.5*std::max(fabs(al), fabs(cl->ar))*(ul - cl->ur);

    u = m_timestepper.get_unew(u, flux, dt);
}

void Cell::update(const double unew)
{
    u = unew;
    double du = deriv();

    ul = u - 0.5*m_delta*du;
    ur = u + 0.5*m_delta*du;
    fl = flux_l();
    fr = flux_r();
    al = a_l();
    ar = a_r();
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
    output << "u = " << c.u << "\n" << "ul = " << c.ul << "\n" << "ur = " << c.ur << "\n";

    return output;
}
