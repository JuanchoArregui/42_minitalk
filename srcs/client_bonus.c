/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/22 14:46:40 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_com_state	com;

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


void	print_bit(int current_bit)
{
	if (com.bit_index == 7)
		print_char_to_send(com.message[com.char_index]);
	print_bit_to_send(current_bit);
}


void	check_server(int check)
{
	if (check == -1)
	{
		if (DEBUG)
			ft_printf("\n❌ ERROR: PID doesnt exist or not listening\n");
		exit(0);
	} 
	else if (!com.server_checked)
	{
		com.server_checked = com.server_pid;
		if (DEBUG)
			ft_printf("\n✅ SERVER with PID: %d is listening\n",
				com.server_checked);
	}
}

pid_t	check_pid(const char *pid_string)
{
	size_t	i;
	pid_t	server_pid;

	i = 0;
	while (pid_string[i])
	{
		if (!ft_isdigit(pid_string[i]))
		{
			if (DEBUG)
				ft_printf("\n❌ ERROR: string fot PID must be just numbers\n");
			exit(0);
		}
		i++;
	}
	server_pid = ft_atoi(pid_string);
	return (server_pid);
}






void	send_current_bit_signal()
{
	int		current_bit;
	int		check;

	current_bit = (com.message[com.char_index] >> com.bit_index) & 1;
	if (current_bit == 1)
		check = kill(com.server_pid, SIGUSR1);
	else
		check = kill(com.server_pid, SIGUSR2);
	check_server(check);
	print_bit(current_bit);
}

void	handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
	{
		//Señal de confirmación de bit
		com.bit_index--;
		if (DEBUG)
			ft_printf("Received confirmation\n");
		// Si todos los bits de un carácter han sido enviados, pasar al siguiente carácter
        if (com.bit_index < 0)
		{
			com.bit_index = 7;
			com.char_index++;
		}
	}
	else if (signal == SIGUSR2)
	{
		//Señal de fin transmisión
		if (DEBUG)
			ft_printf("✅ Terminada transmisión bit 0\n");
	}
}


int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_printf("Error. Usage: ./client <server pid> <message>\n");
		exit(0);
	}
	com.message = argv[2];
	com.server_pid = check_pid(argv[1]);
	com.server_checked = 0;
	com.char_index = 0;
	com.char_length = (int)ft_strlen(argv[2]);
	com.temp_char = com.message[0];//?? este creo que no lo uso
	com.bit_index = 7;
	signal(SIGUSR1, handle_read_receipt);
	signal(SIGUSR2, handle_read_receipt);

	send_current_bit_signal();

	while (com.char_index < com.char_length)
	{
		pause();
		send_current_bit_signal();
	}
		
	return (0);
}

//make bonus CFLAGS+=" -DDEBUG=1"

//Unicode sample string: 😉ÆƠФڇ👍​



















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
