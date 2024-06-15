/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:26:25 by alribeyr          #+#    #+#             */
/*   Updated: 2024/01/10 19:15:25 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_number(int n, int i)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		i += ft_print_char('-');
		n = n * -1;
	}
	if (n > 9)
	{
		i = ft_print_number(n / 10, i);
	}
	i += ft_print_char(n % 10 + '0');
	return (i);
}

int	ft_print_uns_int(unsigned int n, int i)
{
	if (n > 9)
	{
		i = ft_print_uns_int(n / 10, i);
	}
	i += ft_print_char(n % 10 + '0');
	return (i);
}

int	ft_print_hexa(unsigned int n, char type, int i)
{
	char	*base;

	if (type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (n == 0)
	{
		i += ft_print_char('0');
		return (i);
	}
	if ((n / 16) != 0)
		i = ft_print_hexa(n / 16, type, i);
	i += ft_print_char(base[n % 16]);
	return (i);
}

int	ft_print_pointer(size_t p, int i)
{
	char	*base;

	base = "0123456789abcdef";
	if (i == 0)
	{
		if (p == 0)
		{
			i += ft_print_string("(nil)");
			return (i);
		}
		i += ft_print_char('0');
		i += ft_print_char('x');
	}
	if (p == 0)
	{
		i += ft_print_char('0');
		return (i);
	}
	if ((p / 16) != 0)
		i = ft_print_pointer(p / 16, i);
	i += ft_print_char(base[p % 16]);
	return (i);
}
