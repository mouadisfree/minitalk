/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 05:51:34 by mokatfi           #+#    #+#             */
/*   Updated: 2025/03/28 00:35:36 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_client_pid;

void	ft_processing(int sig, unsigned char *character, int *bit_counter)
{
	if (sig == SIGUSR1)
		*character = (*character << 1) | 1;
	else if (sig == SIGUSR2)
		*character = (*character << 1);
	(*bit_counter)++;
}

void	ft_printing(unsigned char *character, int *bit_counter)
{
	if (*bit_counter == 8)
	{
		if (*character == '\0')
			write(1, "\n", 1);
		else
			write(1, character, 1);
		*bit_counter = 0;
		*character = 0;
	}
}

void	server_sigint_handler(int sig)
{
	(void)sig;
	if (g_client_pid > 0)
		kill(g_client_pid, SIGUSR2);
	exit(0);
}

void	ft_hundling_signal(int sig, siginfo_t *info, void *u)
{
	static int				bit_counter;
	static unsigned char	character;
	static int				current_pid;

	(void)u;
	if (!g_client_pid)
		g_client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (g_client_pid != current_pid)
	{
		bit_counter = 0;
		character = 0;
		g_client_pid = current_pid;
	}
	signal(SIGINT, server_sigint_handler);
	ft_processing(sig, &character, &bit_counter);
	ft_printing(&character, &bit_counter);
	if (info && info->si_pid > 0)
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;
	int					pid;

	pid = getpid();
	ft_printf("\n\t███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗██╗\n");
	ft_printf("\t██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝\n");
	ft_printf("\t██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗\n");
	ft_printf("\t██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\n");
	ft_printf("\t╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
	ft_printf("\n\t  PID: %d\t\t\t         By: mokatfi 🕊\n", pid);
	ft_printf("\t⊱ ──────────── {.⋅ ⋆ ᴡ ᴇ ʟ ᴄ ᴏ ᴍ ᴇ ⋆ ⋅.} ────────────── ⊰\n\n");
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_hundling_signal;
	sigemptyset(&action.sa_mask);
	if (sigaction(SIGUSR1, &action, NULL) == -1 || sigaction(SIGUSR2, &action,
			NULL) == -1)
	{
		ft_printf("Error : failed to set up the signal handler\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
