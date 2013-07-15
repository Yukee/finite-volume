#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>

// Solvers
#include "FD1Solver.h"
#include "timeSolver.h"
#include "EulerSolver.h"
//#include "RK2Solver.h"
#include "RK3Solver.h"

// Containers
#include "Vector.h"
#include "ScalarField.h"
#include "PeriodicField.h"
#include "NullField.h"
#include "PrescribedField.h"
#include "Equation.h"

// Functions
#include "Flux.h"
#include "ZeroFlux.h"
#include "BurgersFlux1D.h"
#include "NSFlux.h"
#include "Flume2DConvectionFlux.h"
#include "Flume2DConvectionFluxNoVel.h"
#include "Flume2DSource.h"

#include "WriteVectorField.h"

// Flume pb
//#include "Flume3D.h"
#include "Flume2D.h"

using namespace std;
int main()
{
  int dim = 1;
  Vector<double> dx(dim,1); dx[0] = 0.12566370614359174; Vector<double> xI(dim); xI[0]=2*M_PI; Vector<double> llc(dim,0);
  Flux *ptrCF = new Burgers1D();
  Flux *ptrDF = new ZeroFlux(1,1);
  Flux *ptrS = new ZeroFlux(1,1);
  Equation *eq = new Equation(ptrCF, ptrDF, ptrS); //don't forget to set the sr and velocity somewhere!!
  FD1Solver sol(dx, xI, eq, llc);

  Vector<int> xr (dim); for(int d=0;d<dim;d++) xr[d] = xI[d]/dx[d];
  VectorField pos = sol.get_position();

  //Sets initial fields 
  VectorField u(1, SField (xr));

  for(int it=0;it<u[0].get_size();++it)
    {
      u[0][it] = sin(pos[0][it]);
    }

  double dt = 0.05; double T = 2;
  EulerSolver ts(dt, T, &sol, u);
  ts.get_solution("BurgersTest",0.1);

  return 0;
}
