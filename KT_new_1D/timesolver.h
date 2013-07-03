#ifndef TIMESOLVER_H
#define TIMESOLVER_H

class TimeSolver
{

public:
    TimeSolver();

    // return
    virtual double get_unew(double u, double dudt, double dt);
};

#endif // TIMESOLVER_H
