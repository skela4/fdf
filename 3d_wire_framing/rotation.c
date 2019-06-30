#include "example.h"

void	rotate_Z(t_point **pt, int cols, int rows, int angle)
{
	int	i;
	int	y;
	int	x;
	float	sin_theta;
	float	cos_theta;

	i = 0;
	y = 0;
	x = 0;
	sin_theta = -sin(angle);
	cos_theta = -cos(angle);
	while (i < rows * cols)
	{
		y = (*pt)[i].y;
		x = (*pt)[i].x;
		(*pt)[i].y = (int)((float)y * cos_theta + (float)x * sin_theta);
		(*pt)[i].x = (int)((float)x * cos_theta - (float)y * sin_theta);
		i++;
	}

}
