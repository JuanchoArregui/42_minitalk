/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/11 18:44:52 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	action(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_printf("\nConfirmed num. of received characters by the server: %d", received);
		exit(0);
	}
}

void	send_end_signal(int pid)
{
	int		i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	send_char(int pid, char c)
{
	int		i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
		{
			kill(pid, SIGUSR2);
			if (DEBUG)
				ft_printf("%c", '1');
		}
		else
		{
			kill(pid, SIGUSR1);
			if (DEBUG)
				ft_printf("%c", '0');
		}
		usleep(100);
	}
	if (DEBUG)
			ft_printf("%c", ' ');
}

void	send_string(int pid, char *str)
{
	char	c;

	if (DEBUG)
		ft_printf("\n Sending bits for the string: ");
	while (*str)
	{
		c = *str++;
		send_char(pid, c);
	}
	send_end_signal(pid);
}

int	main(int argc, char **argv)
{
	int pid;
	
	if (DEBUG)
		ft_printf("Debug mode is ON\n");
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);

	pid = ft_atoi(argv[1]);

	ft_printf("Starting CLIENT");
	ft_printf("\nTrying to send %d characters from the string: \"%s\"", ft_strlen(argv[2]), argv[2]);
	ft_printf("\nto the SERVER with PID: %d\n", pid);
	
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_string(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
