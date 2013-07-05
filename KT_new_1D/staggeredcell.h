#ifndef STAGGEREDCELL_H
#define STAGGEREDCELL_H

#include "cell.h"
#include "nt.h"

/* Used with NT scheme (see nt.h for details) */

class SpatialSolver;

class StaggeredCell : public Cell
{
public:
    StaggeredCell();
    StaggeredCell(const double dx, const double dt);

    virtual void evolve();

    virtual std::ostream & operator<<(std::ostream & output);
};

#endif // STAGGEREDCELL_H
