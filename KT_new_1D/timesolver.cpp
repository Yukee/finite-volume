#include "timesolver.h"

TimeSolver::TimeSolver()
{
}

double TimeSolver::get_unew(double u, double dudt, double dt)
{
    // Euler solver
    return u + dt*dudt;
}
