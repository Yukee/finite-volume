#include "cell.h"
#include <iostream>

#include "spatialsolver.h"
#include "lxf.h"
#include "kt1.h"
#include "kt2.h"

#include "burgers.h"
#include "lin.h"
#include "const.h"

double Cell::deriv()
{
    return lim_->get( (u_ - cl->u)/dx_, (cr->u - u_)/dx_ );
}

Cell::Cell()
{
    *this = Cell (1,1);
}

Cell::Cell(const double dx, const double dt)
{
    lim_ = new Limiter();
    timestepper_ = new TimeSolver();
    method_ = new KT2();

    flux_fun_ = new Burgers();
    a_fun_ = new Lin();

    cl = NULL;
    cr = NULL;

    dx_ = dx;
    dt_ = dt;
}

Cell::~Cell()
{
    if(lim_) delete lim_;
    if(timestepper_) delete timestepper_;
    if(method_) delete method_;
    if(flux_fun_) delete flux_fun_;
    if(a_fun_) delete a_fun_;
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
    double dudt = -(1/dx_)*method_->get_flux(this);

    u_ = timestepper_->get_unew(u, dudt, dt_);
}

void Cell::update()
{
    u = u_;

    dudx = deriv();

    ul = u_ - 0.5*dx_*dudx;
    ur = u_ + 0.5*dx_*dudx;
    f = flux_fun_->evaluate(u_);
    fl = flux_fun_->evaluate(ul);
    fr = flux_fun_->evaluate(ur);
    al = a_fun_->evaluate(ul);
    ar = a_fun_->evaluate(ur);
}

void Cell::set_u(double U)
{
    u_ = U;
}

Function * Cell::get_f()
{
    return flux_fun_;
}


std::ostream & Cell::operator<<(std::ostream & output)
{
    output << "Je suis une cellule 1D\n";
    output << "dx = " << dx_ << "\n";
    output << "dt = " << dt_ << "\n";
    output << "Je contiens les valeurs suivantes :" << "\n";
    output << "u = " << u << "\n" << "ul = " << ul << "\n" << "ur = " << ur << "\n";
    output << "J'utilise une methode a " << method_->get_n() << " points\n";

    if(cr && cl) output << "Je connais mes voisines :)\n";
    else output << "Je ne connais pas mes voisines :'(\n";

    return output;
}
