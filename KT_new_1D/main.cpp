#include <iostream>
#include <math.h>
#include "ij/Vector.h"
#include <vector>

#include "cell.h"
#include "copycell.h"
#include "cellarray.h"

#include "limiter.h"
#include "timesolver.h"
#include "spatialsolver.h"
#include "lxf.h"

using namespace std;
using namespace ij;

typedef Vector<Cell *> grid;

int main()
{
    int n = 10;
    double dx = 0.01;
    double dt = 0.01;
    Cell *pc [n];

    // create the actual cells
    pc[0] = new CopyCell(dx, dt, -1);
    pc[n-1] = new CopyCell(dx, dt, 1);
    for(int i=1;i<n-1;i++)
    {
        pc[i] = new Cell(dx, dt);
    }

    // linkage
    pc[0]->cr = pc[1];
    pc[n-1]->cl = pc[n-2];
    for(int i=1;i<n-1;i++)
    {
        pc[i]->cl = pc[i-1];
        pc[i]->cr = pc[i+1];
    }

    // set initial values
    for(int i=0;i<n;i++)
    {
        pc[i]->u = i*dx;
    }

    // update cell with the new u value
    for(int i=0;i<n;i++)
    {
        pc[i]->update();
    }

    *pc[2] << cout;

    CellArray ca(0.1, 2*M_PI, 0);
    vector<Cell *> g = ca.get_grid();

    ca.evolve(10, 0.1, "test");

    return 0;
}
