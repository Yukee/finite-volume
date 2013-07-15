#include <iostream>
#include <vector>

#include "cellarray.h"

using namespace std;

int main()
{
    CellArray ca(8, 100, -1);

    ca.solve(2, 0.1, "leveque/11.5/burgers");

    return 0;
}
