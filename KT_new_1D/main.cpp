#include <iostream>
#include <math.h>
#include "ij/Vector.h"

#include "cell.h"
#include "copycell.h"

using namespace std;
using namespace ij;

typedef Vector<Cell *> grid;

int main()
{
    Cell c(0.01);
    Cell *ptrc;
    ptrc = new CopyCell(0.05,1);

    cout << *ptrc << endl;
    return 0;
}
