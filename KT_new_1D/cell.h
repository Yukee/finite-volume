#ifndef CELL_H
#define CELL_H

#include "limiter.h"
#include "timesolver.h"
#include "function.h"

#include <fstream>
#include <math.h> // fabs

class SpatialSolver;

class Cell
{
protected:
    // field value at the centre (before update)
    double u_;

    // size of the cell
    double dx_;

    // timestep
    double dt_;

    // flux function
    Function *flux_fun_;

    // wavespeed function
    Function *a_fun_;

    // liminter used to get the derivative
    Limiter *lim_;

    // return limited derivative at the centre
    virtual double deriv();

    // time evolution
    TimeSolver *timestepper_;

    // flux computation
    SpatialSolver *method_;

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

    virtual void set_u(double U);

    // field value at the centre
    double u;

    // derivative
    double dudx;

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

    Function * get_f();

    // pointers to neighbouring cells
    Cell *cl;
    Cell *cr;

    // print infos about the cell
    // usage: cell << cout;
    virtual std::ostream & operator<<(std::ostream & output);

};

#endif // CELL_H
