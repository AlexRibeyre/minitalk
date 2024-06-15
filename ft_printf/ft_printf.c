/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:24:28 by alribeyr          #+#    #+#             */
/*   Updated: 2024/01/09 18:24:50 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_forms(char c, va_list *args, int *size)
{
	if (c == 'c')
		*size += ft_print_char(va_arg(*args, int));
	else if (c == '%')
		*size += ft_print_char('%');
	else if (c == 's')
		*size += ft_print_string(va_arg(*args, char *));
	else if (c == 'd' || c == 'i')
		*size += ft_print_number(va_arg(*args, int), 0);
	else if (c == 'u')
		*size += ft_print_uns_int(va_arg(*args, unsigned int), 0);
	else if (c == 'x')
		*size += ft_print_hexa(va_arg(*args, unsigned int), 'x', 0);
	else if (c == 'X')
		*size += ft_print_hexa(va_arg(*args, unsigned int), 'X', 0);
	else if (c == 'p')
		*size += ft_print_pointer(va_arg(*args, size_t), 0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;
	int		i;

	if (!format || *format == '\0')
		return (0);
	size = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_forms(format[i + 1], &args, &size);
			i = i + 2;
		}
		else
		{
			size += ft_print_char(format[i]);
			i++;
		}
	}
	va_end(args);
	return (size);
}
