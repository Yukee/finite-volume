#include "kt1.h"

KT1::KT1()
{
    n_ = 3;
}


double KT1::get_flux(Cell *c)
{
    // left and right waves (see Leveque for the definition)
    double wl = c->u - c->cl->u;
    double wr = c->cr->u - c->u;

    return 0.5*( - fabs(c->ar)*wr + fabs(c->al)*wl + c->cr->f - c->cl->f );
}
