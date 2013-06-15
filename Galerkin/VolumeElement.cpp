#include "VolumeElement.h"

double VolumeElement::m_left_shape_func(double s)
{
	return 0.5*(1-s);
}

double VolumeElement::m_right_shape_func(double s)
{
	return m_left_shape_func(-s);
}

double VolumeElement::interpolated_x(double s)
{
	return m_left_shape_func(s)*X[0] + m_right_shape_func(s)*X[1];
}
	
double VolumeElement::interpolated_u(double s)
{
	return m_left_shape_func(s)*U[0] + m_right_shape_func(s)*U[1];
}
	
double VolumeElement::flux(double u)
{
	return  u;
}
	
double VolumeElement::integrate_flux()
{
	double sqrt3inverse = 0.57735026919;
	return flux(interpolated_u(-sqrt3inverse)) + flux(interpolated_u(sqrt3inverse));
}
	
double VolumeElement::h(double u_left, double u_right)
{
	// Use LxF scheme in the special linear case where df/du = 1
	return 0.5*(  flux(u_left) + flux(u_right) ) - 0.5*(u_right - u_left);
}

void VolumeElement::timestep(double dt)
{
	// Solve the system of 2 eq given by the Galerkin method
	Vector<double> total_flux (2);
	
	total_flux[0] = (2/(X[1] - X[0])) * ( flux(U[0]) + h(left_neighbour_pt->U[1], U[0]) );
	total_flux[1] = (2/(X[1] - X[0])) * ( flux(U[1]) - h(U[1], right_neighbour_pt->U[0]) );
	
	// Need to implement matrices
	double temp_product;
	for(int i=0;i<2;i++)
	{
		temp_product = 0;
		for(int j=0;j<2;j++)
		{
			temp_product += m_mass_matrix_inverse[i][j]*total_flux[j];
		}
		total_flux[i] = temp_product;
	}
	
	// Use Euler method for timestepping
	U = U + dt*total_flux;
}
