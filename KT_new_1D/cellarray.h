#ifndef CELLARRAY_H
#define CELLARRAY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream> // print to file
#include <stdexcept> // invalid_argument
#include <math.h> // initialization

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
    int ni_; // number of inner cells
    int no_; // number of outer (ie ghost) cells
    int n_; // total number of cells
    double llc_;
    double dx_;
    double dt_;

    std::vector<Cell *> grid_;

    // create the actual cells
    void create();

    // linkage
    void link();

    // plug in initial data
    void initialize();

    // update cells content
    void update();

    // t -> t + dt
    void evolve();

    // print current state to file
    void print(std::fstream & data);

public:
    // create an array of N+{numb of boundary cells} cells in a region of size L starting at point llc
    CellArray(double L, int N, double llc);

    std::vector<Cell *> get_grid();

    // timestepping. T: end time, t: time interval between 2 saves
    void solve(double T, double t, std::string name);
};

#endif // CELLARRAY_H
