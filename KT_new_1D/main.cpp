#include <iostream>
#include <math.h>
#include "ij/Vector.h"

#include "cell.h"
#include "limiter.h"

using namespace std;
using namespace ij;

typedef Vector<Cell *> grid;

int main()
{
    int n = 3;

    Cell *ptrc = new Cell [n]; // actual cells
    grid g (n); // vector storing pointers to the actual cells
    for(int i=0;i<n;i++) g[i] = &ptrc[i]; // don't forget to initialise the vector!

    // link border cells
    ptrc[0].cl = &ptrc[n-1]; ptrc[0].cr = &ptrc[1];
    ptrc[n-1].cl = &ptrc[n-2]; ptrc[n-1].cr = &ptrc[0];

    // link inner cells
    for(int i=1;i<n-1;i++)
    {
        ptrc[i].cl = &ptrc[i-1];
        ptrc[i].cr = &ptrc[i+1];
    }

    // give size and affect values to the cells
    double delta = 1;
    for(int i=0;i<n;i++)
    {
        g[i]->set_delta(delta);
        ptrc[i] = delta*i;
    }

    cout << *g[1];

    delete [] ptrc;
    return 0;
}
