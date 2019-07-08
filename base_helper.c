/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:06:11 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 13:41:05 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					hc_to_hi(char c)
{
	int				value;

	value = -1;
	if (c >= '0' && c <= '9')
		value = (int)c - '0';
	if (c >= 'A' && c <= 'F')
		value = (int)c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		value = (int)c - 'a' + 10;
	return (value);
}

int					atoi_base(const char *str, int base)
{
	int				len;
	int				power;
	long			num;
	long			sign;

	len = 0;
	power = 1;
	num = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		sign = (*(str++) == '-') ? -1 : 1;
	len = ft_strlen(str) - 1;
	while (len >= 0 && ((str[len] >= 9 && str[len] <= 13) || str[len] == 32))
		len--;
	while (len >= 0 && (hc_to_hi(str[len]) >= 0 && hc_to_hi(str[len]) < base))
	{
		num += hc_to_hi(str[len--]) * power;
		power = power * base;
	}
	return ((int)(num * sign));
}

int					check_base(const char *str, const char *find)
{
	int				i;

	i = 0;
	while (find[i])
	{
		if (!ft_strchr(str, find[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) > 16)
		return (ft_strlen(str) - 6);
	return (ft_strlen(str));
}

int					detect_base(char *str)
{
	static char		hex[] = "0123456789ABCDEFabcdef";
	static char		dec[] = "0123456789";
	static char		oct[] = "01234567";
	static char		bin[] = "01";

	if (!str)
		return (0);
	if (!ft_strstr(str, "0B") && !ft_strstr(str, "0X")
			&& !ft_strstr(str, "0b") && !ft_strstr(str, "0x"))
	{
		if (str[0] == '0' && ft_strlen(str) > 1)
			return (check_base(oct, str + 1));
		else
			return (check_base(dec, str));
	}
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		return (check_base(hex, str + 2));
	if (str[0] == '0' && (str[1] == 'b' || str[1] == 'B'))
		return (check_base(bin, str + 2));
	return (0);
}
