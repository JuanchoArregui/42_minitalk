/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/18 16:26:26 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
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
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\0');
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
