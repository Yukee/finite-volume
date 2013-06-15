#ifndef VOLUMEELEMENT_H
#define VOLUMEELEMENT_H

#include "Vector.h"

class VolumeElement
{
	private:
	
	// Interpolation shape function used to interpolate X and U at local coordinate s
	double m_left_shape_func(double s);
	
	double m_right_shape_func(double s);
	
	// Inverse of the mass matrix. Beware !! it equal to the matrix defined in the paper divided by (X[1] - X[0])/2
	Vector< Vector<double> > m_mass_matrix_inverse;
	
	public:
	
	// Pointers to the neighbours
	VolumeElement *left_neighbour_pt;
	VolumeElement *right_neighbour_pt;
	
	// Storage for the coordinates
	Vector<double> X;
	
	// Storage for the unknowns
	Vector<double> U;
	
	// Constructor: initialise the vectors to hold 2 entries, at set up the mass matrix inverse for the linear pb
	VolumeElement()
	{
		X.resize(2);
		U.resize(2);
		m_mass_matrix_inverse.resize(2); for(int i=0;i<2;i++) m_mass_matrix_inverse[i].resize(2);
		
		m_mass_matrix_inverse[0][0] = 2; m_mass_matrix_inverse[1][1] = 2;
		m_mass_matrix_inverse[1][0] = -1; m_mass_matrix_inverse[0][1] = -1;
	}
	
	// Return the value of the coordinate at the local coordinate s
	double interpolated_x(double s);
	
	// Return the value of the unknown at the local coordinate s
	double interpolated_u(double s);
	
	// Calculate the flux; by default the flux is assumed to be linear
	virtual double flux(double u);
	
	// Calculate the intergral of the flux function over the volume element using gaussian two-points rule
	double integrate_flux();
	
	// Return the numerical flux; by default uses the Lax-Friedrich scheme
	virtual double h(double u_left, double u_right);
	
	// Updates values of the unknowns U at volume element edges
	void timestep(double dt);
};

#endif
