#include "staggeredcell.h"

#include "burgers.h"
#include "lin.h"
#include "const.h"

StaggeredCell::StaggeredCell()
{
    *this = StaggeredCell(1,1);
}

StaggeredCell::StaggeredCell(const double dx, const double dt)
{
    lim_ = new Limiter();
    timestepper_ = new TimeSolver();
    method_ = new NT();

    flux_fun_ = new Burgers();
    a_fun_ = new Lin();

    cl = NULL;
    cr = NULL;

    dx_ = dx;
    dt_ = dt;
}

void StaggeredCell::evolve()
{
    // sending the left neighbouring cell to get the flux at the current cell
    double dudt = -(1/dx_)*method_->get_flux(cl);

    u_ = timestepper_->get_unew(u, dudt, dt_);
}

std::ostream & StaggeredCell::operator<<(std::ostream & output)
{
    output << "Je suis une cellule de type StaggeredCell\n";

    return Cell::operator <<(output);
}
