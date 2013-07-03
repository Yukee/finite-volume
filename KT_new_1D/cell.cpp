#include "cell.h"
#include <iostream>

#include "spatialsolver.h"
#include "lxf.h"

double Cell::deriv()
{
    return lim_->get( (u - cl->u)/dx_, (cr->u - u)/dx_ );
}

Cell::Cell()
{
    *this = Cell (1,1);
}

Cell::Cell(const double dx, const double dt)
{
    lim_ = new Limiter();
    timestepper_ = new TimeSolver();
    flux_ = new LxF();

    cl = NULL;
    cr = NULL;

    dx_ = dx;
    dt_ = dt;
}

Cell::~Cell()
{
    if(lim_) delete lim_;
    if(timestepper_) delete timestepper_;
    if(flux_) delete flux_;
}

void Cell::set_dx(double dx)
{
    dx_ = dx;
}

void Cell::set_dt(double dt)
{
    dt_ = dt;
}

double Cell::dx()
{
    return dx_;
}

double Cell::dt()
{
    return dt_;
}

double Cell::get_max_dt()
{
    // max Courant number for advection equation using LxF scheme
    double nu_max = 1;

    return dx_*nu_max;
}

void Cell::evolve()
{
    update();

    double flux = flux_->get_flux(this);

    u = timestepper_->get_unew(u, flux, dt_);
}

void Cell::update()
{
    double du = deriv();

    ul = u - 0.5*dx_*du;
    ur = u + 0.5*dx_*du;
    f = flux();
    fl = flux_l();
    fr = flux_r();
    al = a_l();
    ar = a_r();
}

// linear flux

double Cell::flux()
{
    return u;
}

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

std::ostream & Cell::operator<<(std::ostream & output)
{
    output << "Je suis une cellule 1D\n";
    output << "dx = " << dx_ << "\n";
    output << "dt = " << dt_ << "\n";
    output << "Je contiens les valeurs suivantes :" << "\n";
    output << "u = " << u << "\n" << "ul = " << ul << "\n" << "ur = " << ur << "\n";
    output << "J'utilise une methode a " << flux_->get_n() << " points\n";

    if(cr && cl) output << "Je connais mes voisines :)\n";
    else output << "Je ne connais pas mes voisines :'(\n";

    return output;
}
