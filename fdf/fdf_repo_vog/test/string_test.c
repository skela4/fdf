/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 05:49:27 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/02 05:46:33 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gnl/libft/libft.h"
#include "gnl/get_next_line.h"

int		count_word(const char *str);
int		hc_to_hi(char c);
int		atoi_base(const char *str, int base);
int		detect_base(char *str);
int		check_base(char *str, char *find);
int		count_line(const char *file);
int		check_equal_line(const char *file, int fd, char *line, int lcount);

int		main(int argc, char **argv)
{
/*
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;


	s1 = "26";
	s2 = "0x26";
	s3 = "0X42";
	s4 = "0B01110100";

	printf("base = %d\n", detect_base(s1));
	printf("base = %d\n", detect_base(s2));
	printf("base = %d\n", detect_base(s3));
	printf("base = %d\n", detect_base(s4));
*/
	(void)argc;
	ft_putnbr(check_equal_line(argv[1], 0, NULL));

	return (0);
}
