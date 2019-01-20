/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:53:21 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/01/20 10:32:52 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		size_x;
	int		size_y;
	char	*title;

	size_x = 600;
	size_y = 400;
	title = "mlx_42";

	if (!(mlx_ptr = mlx_init()))
		return (0);
	printf("connection established\n");
	if (!(win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title)))
		return (0);
	printf("window created\n");

	mlx_loop(mlx_ptr);
	return (0);
}
