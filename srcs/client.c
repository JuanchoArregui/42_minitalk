/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/07 14:51:16 by jarregui         ###   ########.fr       */
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
	if (DEBUG)
		ft_printf("DEBUG.\nSending message to PID: %s\n", argv[0]);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, END_TRANSMISSION);
	return (0);
}

// void	check_pid_str_is_digit(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (!ft_isdigit(s[i]))
// 		{
// 			if (DEBUG)
// 				ft_printf("\nERROR: string fot PID must be just numbers");
// 			exit(0);
// 		}
// 		i++;
// 	}
// }

// void	check_pid_is_listening(pid_t server_pid)
// {
// 	if (kill(server_pid, SIGUSR1) == -1) {
// 		if (DEBUG)
// 			ft_printf("\nERROR: provided PID doesnt exist or not listening");
// 		exit(0);
// 	} 
// 	else
// 	{
// 		if (DEBUG)
// 			ft_printf("\nSERVER with PID: %d is listening", (int)server_pid);
// 	}
// }







// void	action(int sig)
// {
// 	static int	received = 0;

// 	ft_printf("****"); 


// 	if (sig == SIGUSR1)
// 		++received;
// 	else
// 	{
// 		ft_printf("\nConfirmed num. of received characters by the server: %d", received);
// 		exit(0);
// 	}
// }

// void	send_char_signals(pid_t server_pid, char c)
// {
// 	int		i;

// 	i = 8;
// 	while (i--)
// 	{
// 		if (c >> i & 1)
// 		{
// 			kill(server_pid, SIGUSR2);
// 			if (DEBUG)
// 				ft_printf("%c", '1');
// 		}
// 		else
// 		{
// 			kill(server_pid, SIGUSR1);
// 			if (DEBUG)
// 				ft_printf("%c", '0');
// 		}
// 		usleep(MICROSECS);
// 	}
// 	if (DEBUG)
// 		ft_printf("%c", ' ');
// }

// void	send_end_signal(pid_t server_pid)
// {

// 	ft_printf("\nantes de enviar señal END TRASMISION");

// 	send_char_signals(server_pid, END_TRANSMISSION);

// 	ft_printf("\nenviada señal END TRASMISION");
// }

// void	send_string(int pid, char *str)
// {
// 	char	c;

// 	if (DEBUG)
// 		ft_printf("\nSending bits:\n");
// 	while (*str)
// 	{
// 		c = *str++;
// 		send_char_signals(pid, c);
// 	}
// 	send_end_signal(pid);
// }

// int	main(int argc, char **argv)
// {
// 	pid_t server_pid;
	
// 	if (DEBUG)
// 		ft_printf("\nStarting CLIENT");
// 	if (argc != 3 || !ft_strlen(argv[2]))
// 		return (1);
// 	check_pid_str_is_digit(argv[1]);
// 	server_pid = (pid_t)ft_atoi(argv[1]);
// 	check_pid_is_listening(server_pid);




	
// 	ft_printf("\nTrying to send %d characters from the string: \"%s\"", ft_strlen(argv[2]), argv[2]);
	
	
// 	signal(SIGUSR1, action);
// 	signal(SIGUSR2, action);
// 	send_string(server_pid, argv[2]);
// 	while (1)
// 		pause();
// 	return (0);
// }

//Info sobre manipulación de bits:
//https://nomadaselectronicos.wordpress.com/2015/03/05/manipulacion-de-bits-en-c-y-aplicaciones/
