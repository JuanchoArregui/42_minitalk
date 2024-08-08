/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/08 11:46:10 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_char_to_send(unsigned char character)
{
	if (DEBUG)
	{
		write(1, "\n", 1);
		if (character == END_TRANSMISSION)
			write(1, "END_TRANSMISSION", 16);
		else
			write(1, &character, 1);
		write(1, " - ", 3);
	}
}

void	print_bit_to_send(int bit)
{
	char	c;

	if (DEBUG)
	{
		c = bit + 48;
		write(1, &c, 1);
	}
}

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;
	int				signal;
	int				bit;

	i = 8;
	temp_char = character;
	print_char_to_send(character);
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		bit = temp_char % 2;
		print_bit_to_send(bit);
		if (bit == 0)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		kill(pid, signal);
		usleep(MICROSECS);
	}
}

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;
	int			i;

	if (argc != 3)
	{
		ft_printf("Error. Usage: ./client <server pid> <message>\n");
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	if (DEBUG)
		ft_printf("DEBUG.\nSending message to PID: %d\n", server_pid);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, END_TRANSMISSION);
	return (0);
}
