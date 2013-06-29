#ifndef CELL_H
#define CELL_H

#include "limiter.h"
#include <fstream>

class Cell
{
protected:
    // size of the cell
    double m_delta;

    // field value at the centre
    double m_u;

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

public:
    Cell();
    Cell(const double delta);

    // set cell size
    void set_delta(double delta);

    // update m_u, ul, ur, fl, fr, al, ar (after timestepping)
    Cell & operator=(const double & u);

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
