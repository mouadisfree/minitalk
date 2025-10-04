/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 05:51:55 by mokatfi           #+#    #+#             */
/*   Updated: 2025/03/28 02:19:56 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_x;

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	if ((nptr[i] >= 'a' && nptr[i] <= 'z') || (nptr[i] >= 'A'
			&& nptr[i] <= 'Z'))
		return (0);
	return (result * sign);
}

void	ft_sending_signal(int pid, unsigned char c)
{
	int	bit;
	int	kill_check;

	kill_check = 0;
	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill_check = kill(pid, SIGUSR1);
		else
			kill_check = kill(pid, SIGUSR2);
		if (kill_check == -1)
			ft_printf("Error ​​❌​ : failed to send signal\n");
		while (!g_x)
			usleep(60);
		g_x = 0;
		bit--;
	}
}

void	ft_acknowledge(int signal_number)
{
	(void)signal_number;
	g_x = 1;
}

void	client_stop_handler(int sig)
{
	(void)sig;
	ft_printf("Server stopped. Client terminating...\n");
	exit(0);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
	{
		ft_printf("True use✅​👉​​  ./client <pid> <message>\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0 || kill(pid, 0) < 0)
	{
		ft_printf("Error: Invalid PID\n");
		exit(1);
	}
	signal(SIGUSR1, ft_acknowledge);
	signal(SIGUSR2, client_stop_handler);
	i = 0;
	while (av[2][i])
		ft_sending_signal(pid, av[2][i++]);
	ft_sending_signal(pid, '\0');
	return (0);
}
