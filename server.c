/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:36:05 by alex              #+#    #+#             */
/*   Updated: 2024/06/15 11:02:15 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_int_or_char = 0;

void	write_string(char *str, char *c, siginfo_t *info)
{
	static int	j = 0;

	str[j] = *c;
	if (str[j] == '\0')
	{
		kill(info->si_pid, SIGUSR1);
		ft_printf("Client sent the message :\n%s\n", str);
		free(str);
		str = NULL;
		g_int_or_char = 0;
		j = -1;
	}
	j++;
}

void	receive_bits(int *len, char *c, int i, int sig)
{
	if (g_int_or_char == 0)
	{
		if (sig == SIGUSR1)
			*len |= 1 << i;
		else
			*len &= ~(1 << i);
	}
	else
	{
		if (sig == SIGUSR1)
			*c |= 1 << i;
		else
			*c &= ~(1 << i);
	}
}

void	start_count(siginfo_t *info, char *str, int *i)
{
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("Error in reaching PID : %d\n", info->si_pid);
		if (str)
			free(str);
		exit(EXIT_FAILURE);
	}
	if (*i < 0)
	{
		if (g_int_or_char == 0)
			*i = 31;
		else
			*i = 7;
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	len = 0;
	static char	c = 0;
	static int	i = -1;
	static char	*str;

	(void)context;
	start_count(info, str, &i);
	receive_bits(&len, &c, i, sig);
	if (i == 0)
	{
		if (g_int_or_char == 0)
		{
			str = malloc(sizeof(char) * (len + 1));
			g_int_or_char = 1;
		}
		else
			write_string(str, &c, info);
	}
	i--;
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		sleep(1);
	return (0);
}
