/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/22 15:20:16 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_bit_signal(int bit_index, int signal)
{
	if (DEBUG)
	{
		if (bit_index == 0)
			write(1, "\n", 1);
		if (signal == SIGUSR1)
			write(1, "1", 1);
		else if (signal == SIGUSR2)
			write(1, "0", 1);
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	kill(client_pid, SIGUSR1); //confirmamos recepción bit

	print_bit_signal(bit_index, sig);
	current_char |= (sig == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
		{
			write(1, "\n", 1);
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		else
		{
			write(1, " - ", 3);
			write(1, &current_char, 1);
		}
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int main (void)
{
	struct sigaction	s_sigaction;

	if (DEBUG)
		ft_printf("PID: ");
	ft_printf("%d\n", getpid());
	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	if (DEBUG)
		ft_printf("Server with Receipt Confirmation is listening...\n");
	while (1)
		pause();
	return (0);
}

//make bonus CFLAGS+=" -DDEBUG=1"
