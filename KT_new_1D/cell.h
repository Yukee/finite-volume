#ifndef CELL_H
#define CELL_H

#include "limiter.h"
#include "timesolver.h"

#include <fstream>
#include <math.h> // fabs

class SpatialSolver;

class Cell
{
protected:
    // size of the cell
    double dx_;

    // timestep
    double dt_;

    // return flux value at the centre
    virtual double flux();

    // return flux value at the edges
    virtual double flux_l();
    virtual double flux_r();

    // return wavespeed value at the edges
    virtual double a_l();
    virtual double a_r();

    // liminter used to get the derivative
    Limiter *lim_;

    // return limited derivative at the centre
    virtual double deriv();

    // time evolution
    TimeSolver *timestepper_;

    // flux computation
    SpatialSolver *flux_;

public:
    Cell();
    Cell(const double dx, const double dt);

    virtual ~Cell();

    // set cell size
    virtual void set_dx(double dx);

    // set timestep
    virtual void set_dt(double dt);

    // getters
    virtual double dx();
    virtual double dt();

    // return the maximal dt respecting CFL condition
    virtual double get_max_dt();

    // do the time evolution: update u, but not the other quantities (they are updated via the update function)
    virtual void evolve();

    // update ul, ur, fl, fr, al, ar (must be done only after every cell has evolved)
    virtual void update();

    // field value at the centre
    double u;

    // flux value at the centre
    double f;

    // flux value at the edges
    double fl;
    double fr;

    // wavespeed value at the edges
    double al;
    double ar;

    // field value at the edges
    double ul;
    double ur;

    // pointers to neighbouring cells
    Cell *cl;
    Cell *cr;

    // print infos about the cell
    // usage: cell << cout;
    virtual std::ostream & operator<<(std::ostream & output);

};

#endif // CELL_H
