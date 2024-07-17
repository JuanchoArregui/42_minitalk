/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/17 14:14:17 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		// ft_putchar_fd(c, 1);
		putchar(c);

		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int main (void)
{
	struct sigaction	s_sigaction;

	printf("Server PID: %d\n", getpid());
	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_sigaction = action;
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


