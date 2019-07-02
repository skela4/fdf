#include "example.h"

void	rotate_Z(t_point **pt, int cols, int rows, double angle)
{
	int	i;
	int	y;
	int	x;
	double	sin_theta;
	double	cos_theta;

	i = 0;
	y = 0;
	x = 0;
	sin_theta = sin(angle);
	cos_theta = cos(angle);

	while (i < rows * cols)
	{
		printf("y = %f x = %f z = %f\n", (*pt)[i].y, (*pt)[i].x, (*pt)[i].z);
		i++;
	}
	i = 0;

	while (i < rows * cols)
	{
		x = (*pt)[i].x;
		y = (*pt)[i].y;
		(*pt)[i].x = x * cos_theta - y * sin_theta;
		(*pt)[i].y = x * sin_theta + y * cos_theta;
		i++;
	}

	i = 0;
	while (i < rows * cols)
	{
		printf("y = %f x = %f z = %f\n", (*pt)[i].y, (*pt)[i].x, (*pt)[i].z);
		i++;
	}

}
