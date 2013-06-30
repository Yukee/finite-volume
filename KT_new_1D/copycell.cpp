#include "copycell.h"

CopyCell::CopyCell(double delta, int boundary) : Cell (delta)
{
    if(boundary == -1 || boundary == 1) m_b = boundary;

    // the cell is at the boundary!
    if(m_b == -1) cl = this;
    if(m_b == 1) cr = this;
}

// no flux is computed, only the value of u is updated. Caution!! The neighbouring inner cell must have evolved BEFORE this function is called.
void CopyCell::evolve(double dt)
{
    Cell::update();

    if(m_b == -1) u = cr->u;
    if(m_b == 1) u = cl->u;
}

std::ostream & CopyCell::operator<<(std::ostream & output)
{
    output << "Je suis une ghost cell de type CopyCell\n";

    return Cell::operator <<(output);
}
