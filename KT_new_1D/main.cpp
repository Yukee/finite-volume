#include <iostream>
#include <math.h>
#include "ij/Vector.h"

#include "cell.h"
#include "copycell.h"
#include "cellarray.h"

using namespace std;
using namespace ij;

typedef Vector<Cell *> grid;

int main()
{
    int n = 10;
    double delta = 0.01;
    Cell *pc [n];

    // create the actual cells
    pc[0] = new CopyCell(delta, -1);
    pc[n-1] = new CopyCell(delta, 1);
    for(int i=1;i<n-1;i++)
    {
        pc[i] = new Cell(delta);
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
        pc[i]->u = i*delta;
    }

    // update cell with the new u value
    for(int i=0;i<n;i++)
    {
        pc[i]->update();
    }

    *pc[2] << cout;
    return 0;
}
