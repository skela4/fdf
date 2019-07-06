/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 05:47:23 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 15:50:13 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			count_word(const char *str)
{
	int		sep;
	int		wc;

	sep = 0;
	wc = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			sep = 0;
		else if (sep == 0)
		{
			sep = 1;
			++wc;
		}
		++str;
	}
	return (wc);
}

int			hc_to_hi(char c)
{
	int		value;

	value = -1;
	if (c >= '0' && c <= '9')
		value = (int)c - '0';
	if (c >= 'A' && c <= 'F')
		value = (int)c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		value = (int)c - 'a' + 10;
	return (value);
}

int			atoi_base(const char *str, int base)
{
	int		len;
	int		power;
	int		num;
	int		sign;

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
	return (num * sign);
}

int			check_base(const char *str, const char *find)
{
	int		i;

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

int			detect_base(char *str)
{
	static const char	hex[] = "0123456789ABCDEFabcdef";
	static const char	dec[] = "0123456789";
	static const char	oct[] = "01234567";
	static const char	bin[] = "01";

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
