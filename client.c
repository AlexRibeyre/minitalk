/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:37:17 by alex              #+#    #+#             */
/*   Updated: 2024/06/15 11:06:25 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_wait = 0;

void	send_char(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_printf("Error in reaching PID : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_wait = 0;
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (g_wait == 0)
			usleep(1000);
	}
}

void	ft_message(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(str[i], pid);
		i++;
	}
	send_char(0, pid);
}

void	send_len(char *str, pid_t pid)
{
	int	i;
	int	j;

	i = 0;
	j = 31;
	while (str[i])
		i++;
	while (j >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_printf("Error in reaching PID : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_wait = 0;
		if (i >> j & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		j--;
		while (g_wait == 0)
			usleep(1000);
	}
	ft_message(str, pid);
}

void	client_handler(int sig)
{
	if (sig == SIGUSR2)
		g_wait = 1;
	else if (sig == SIGUSR1)
	{
		write(1, "Server received the message\n", 28);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "Usage : ./client <PID> <Message>\n", 33);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		write(1, "Wrong PID\n", 10);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &client_handler);
	signal(SIGUSR2, &client_handler);
	send_len(argv[2], pid);
	while (1)
		sleep(1);
	return (0);
}
