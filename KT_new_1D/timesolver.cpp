#include "timesolver.h"

TimeSolver::TimeSolver()
{
}

double TimeSolver::get_unew(double u, double flux, double dt)
{
    // Euler solver
    return u - dt*flux;
}
