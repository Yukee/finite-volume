#include "kt2.h"

KT2::KT2()
{
    n_ = 5;
}

double KT2::get_flux(Cell *c)
{
    // left and right numerical fluxes
    double fr = 0.5*( (c->fr + c->cr->fl) - fabs(c->ar)*(c->cr->ul - c->ur) );
    double fl = 0.5*( (c->fl + c->cl->fr) - fabs(c->al)*(c->ul - c->cl->ur) );

    return fr - fl;

}
