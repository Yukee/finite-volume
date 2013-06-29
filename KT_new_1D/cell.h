#ifndef CELL_H
#define CELL_H

#include "limiter.h"
#include "timesolver.h"
#include <fstream>
#include <math.h> // fabs

class Cell
{
protected:
    // size of the cell
    double m_delta;

    // return flux value at the edges
    virtual double flux_l();
    virtual double flux_r();

    // return wavespeed value at the edges
    virtual double a_l();
    virtual double a_r();

    // liminter used to get the derivative
    Limiter m_lim;

    // return limited derivative at the centre
    virtual double deriv();

    // time evolution
    TimeSolver m_timestepper;

public:
    Cell();
    Cell(const double delta);

    // set cell size
    virtual void set_delta(double delta);

    // do the time evolution: update u, but not the other quantities (they are updated via the update function)
    virtual void evolve(const double dt);

    // update ul, ur, fl, fr, al, ar (must be done only after every cell has evolved)
    virtual void update(const double u);

    // field value at the centre
    double u;

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
    friend std::ostream & operator<<(std::ostream & output, const Cell & c);

};

#endif // CELL_H
