#include <iostream>
#include <vector>

#include "cellarray.h"

using namespace std;

int main()
{
    CellArray ca(2*M_PI, 1100, 0);

    ca.solve(2, 0.1, "test");

    return 0;
}
