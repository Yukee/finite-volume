#include "nt.h"

NT::NT()
{
    n_ = 5;
}

double NT::get_flux(Cell *c)
{
    double dt = c->dt();
    double dx = c->dx();

    // numerical flux derivatives
    double dfrdx = (c->cr->cr->cr->f - c->cr->f)/(2*dx);
    double dfdx = (c->cr->f - c->cl->f)/(2*dx);

    // values after half a timestep
    double ur_half = c->cr->cr->u - 0.5*dt*dfrdx;
    double u_half = c->u - 0.5*dt*dfdx;

    return (-0.5*dx/dt)*(c->cr->cr->u - c->u) + (-dx*dx/(8*dt))*(c->dudx - c->cr->cr->dudx) + (c->get_f()->evaluate(ur_half) - c->get_f()->evaluate(u_half));
}
