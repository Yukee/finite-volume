#include "kt2.h"

KT2::KT2()
{
    n_ = 5;
}

double KT2::get_flux(Cell *c)
{
    // left and right waves (see Leveque for the definition)
    //double wl = c->ul - c->cl->ur;
    //double wr = c->cr->ul - c->ur;

    double wl = c->u - c->cl->u;
    double wr = c->cr->u - c->u;


    double a = c->dx()/c->dt();

    //return 0.5*( - a*wr + a*wl + c->cr->fl + c->fr - c->fl - c->cl->fr );
    return 0.5*( - fabs(c->ar)*wr + fabs(c->al)*wl + c->cr->f - c->cl->f );

}
