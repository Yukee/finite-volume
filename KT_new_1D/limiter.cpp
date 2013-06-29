#include "limiter.h"
#include <algorithm> // min and max

Limiter::Limiter()
{
}

double Limiter::get(const double & a, const double & b)
{
    double minmod;
      if(a*b<=0) minmod = 0;
      else
        {
          if(a>0) minmod = std::min(a,b);
          else minmod = std::max(a,b);
        }
      return minmod;
}
