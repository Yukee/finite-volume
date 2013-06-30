#ifndef CELLARRAY_H
#define CELLARRAY_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept> // invalid_argument

#include "cell.h"

// a couple (double, string) to store infos about boundary conditions
class Bc
{
private:
    // a list of all known bondary condition types
    std::vector<std::string> dictionary_;

    // boundary condition type
    std::string type_;

    // location of the boundary
    int loc_;

public:
    Bc();
    Bc(int loc, std::string type);

    // print available bc types
    void print();

    // return type
    std::string type();

    // return location
    int loc();
};

class CellArray
{
private:

    double l_;
    int n_; // the actual number of cells (greater than N!)
    double llc_;

    Bc left_;
    Bc right_;

    std::vector<Cell *> grid_;

    // create the actual cells
    void create();

    // linkage
    void link();

    // update content of the cells
    void update();

public:
    // create an array of N+{numb of boundary cells} cells in a region of size L starting at point llc
    CellArray(double L, int N, double llc, Bc left, Bc right);
};

#endif // CELLARRAY_H
