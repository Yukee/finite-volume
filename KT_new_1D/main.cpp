#include <iostream>
#include <vector>

#include "cellarray.h"

using namespace std;

int main()
{
    CellArray ca(2*M_PI, 50, 0);

    ca.solve(10, 1, "test");

    return 0;
}
