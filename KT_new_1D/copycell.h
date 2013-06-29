#ifndef COPYCELL_H
#define COPYCELL_H

#include "cell.h"

// Type of ghost cell copying the field value inside the domain outside the domain.

class CopyCell : public Cell
{
private:
    // left (-1) or right (1) boundary
    int m_b;

public:
    CopyCell(double delta, int boundary);

    // update by copying the new value
    virtual void evolve(double dt);

};

#endif // COPYCELL_H
