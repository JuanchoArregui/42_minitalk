/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/17 16:59:24 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static pid_t			client_pid = 0;
	static unsigned char	current_char = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	current_char |= (sig == SIGUSR2);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
		{
			ft_printf("\n");
			kill(client_pid, SIGUSR2);
			return ;
		}
		else
		{
			ft_printf("%c", current_char);
			kill(client_pid, SIGUSR1);
		}
		bit_index = 0;
		client_pid = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int main (void)
{
	struct sigaction	s_sigaction;

	printf("Server PID: %d\n", getpid());
	if (DEBUG)
		ft_printf("Listening...");
	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}

// void main (int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	printf("\nargc %d", argc);
// 	while (i < argc){
// 		printf("\nargv[%d] %s", i, argv[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	printf("\n");
// }


//Info sobre minitalk:  https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24

//https://github.com/hanshazairi/42-minitalk
//https://github.com/leogaudin/minitalk/tree/main


