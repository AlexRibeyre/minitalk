/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:24:59 by alribeyr          #+#    #+#             */
/*   Updated: 2024/02/09 16:19:05 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

int		ft_printf(const char *format, ...);
void	ft_forms(char c, va_list *args, int *size);
int		ft_print_char(char c);
int		ft_print_string(char *str);
int		ft_print_number(int n, int i);
int		ft_print_uns_int(unsigned int n, int i);
int		ft_print_hexa(unsigned int n, char type, int i);
int		ft_print_pointer(size_t p, int i);

#endif