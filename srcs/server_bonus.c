/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/18 16:39:45 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;

	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}


void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static pid_t			client_pid = 0;
	static unsigned char	current_char = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	current_char |= (sig == SIGUSR2) << (7 - bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
		{
			// ft_printf("\n");
			write(1, "\n", 1);
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		else
		{
			write(1, &current_char, 1);
			
			// ft_printf("%c", current_char);
			kill(client_pid, SIGUSR1);
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
