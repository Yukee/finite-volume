#ifndef LIMITER_H
#define LIMITER_H

// This is the minmod limiter. Derive this class to add new limiters.

class Limiter
{
public:
    Limiter();

    // evaluate limiter
    virtual double get(const double &a, const double &b);
};

#endif // LIMITER_H
