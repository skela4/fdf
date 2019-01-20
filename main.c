/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:53:21 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/01/20 12:13:02 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		key_hook(int key, void *param)
{
	ft_putchar(key);
	return (0);
}

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
	if (!(win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title)))
		return (0);
	mlx_pixel_put(mlx_ptr, win_ptr, size_x / 2, size_y / 2, 0xFFFFFF);
	mlx_string_put(mlx_ptr, win_ptr, size_x / 3, size_y / 3, 0xFF00FF, "aleksander");
	mlx_key_hook(win_ptr, &key_hook, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
