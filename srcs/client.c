/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/17 15:41:47 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	check_pid_str_is_digit(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			if (DEBUG)
				ft_printf("\nERROR: string fot PID must be just numbers");
			exit(0);
		}
		i++;
	}
}

void	check_pid_is_listening(pid_t server_pid)
{
	if (kill(server_pid, SIGUSR1) == -1) {
		if (DEBUG)
			ft_printf("\nERROR: provided PID doesnt exist or not listening");
		exit(0);
	} 
	else
	{
		ft_printf("\nSERVER with PID: %d is listening", (int)server_pid);
	}
}







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
		usleep(MICROSECS);
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
		usleep(MICROSECS);
	}
	if (DEBUG)
			ft_printf("%c", ' ');
}

void	send_string(int pid, char *str)
{
	char	c;

	if (DEBUG)
		ft_printf("\nSending bits:\n");
	while (*str)
	{
		c = *str++;
		send_char(pid, c);
	}
	send_end_signal(pid);
}

int	main(int argc, char **argv)
{
	pid_t server_pid;
	
	if (DEBUG)
		ft_printf("\nStarting CLIENT");
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	check_pid_str_is_digit(argv[1]);
	server_pid = (pid_t)ft_atoi(argv[1]);
	check_pid_is_listening(server_pid);




	
	ft_printf("\nTrying to send %d characters from the string: \"%s\"", ft_strlen(argv[2]), argv[2]);
	
	
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_string(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}

//Info sobre manipulación de bits:
//https://nomadaselectronicos.wordpress.com/2015/03/05/manipulacion-de-bits-en-c-y-aplicaciones/
