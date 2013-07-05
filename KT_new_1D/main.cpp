#include <iostream>
#include <vector>

#include "cellarray.h"

using namespace std;

int main()
{
    CellArray ca(2*M_PI, 200, 0);

    ca.solve(20, 1, "test");

    vector<Cell *> g = ca.get_grid();
    *g[20] << cout;
    return 0;
}
