#ifndef EQUATION_H
#define	EQUATION_H

#include "Vector.h"
#include "PeriodicField.h"
#include "NullField.h"
#include "Flux.h"
#include "ZeroFlux.h"

class Equation
{
protected:
  Flux *m_conv; //convection flux
  Flux *m_diff; //diffusion flux
  int m_space_dimensions;
  int m_solved_dimensions;

public:
  Equation() {m_conv =  new ZeroFlux(1,1); m_diff = new ZeroFlux(1,1);
    m_space_dimensions = m_conv->get_space_dimensions();
    m_solved_dimensions = m_conv->get_solved_dimensions();}

  Equation(Flux *f) : m_conv(f) {
    m_space_dimensions = m_conv->get_space_dimensions();
    m_solved_dimensions = m_conv->get_solved_dimensions();
    m_diff = new ZeroFlux(m_space_dimensions,m_solved_dimensions);}

  Equation(Flux *f, Flux *diff) : m_conv(f), m_diff(diff){
    m_space_dimensions = m_conv->get_space_dimensions();
    m_solved_dimensions = m_conv->get_solved_dimensions();
    if( m_space_dimensions != m_diff->get_space_dimensions() || m_solved_dimensions != m_diff->get_solved_dimensions())
      throw std::invalid_argument("In Equation(Flux*,Flux*) convective and diffusive fluxes have different dimensions");}

  Equation(const Equation &);

  ~Equation();

  VectorField get_convectionFlux(const VectorField &, const int);
  VectorField get_diffusionFlux(const VectorField &, const int);
  SField get_max_eigenvalue(const VectorField &, const int);
  int get_space_dimensions();
  int get_solved_dimensions();
};

#endif

