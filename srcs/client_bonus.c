/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:44 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/22 15:25:44 by jarregui         ###   ########.fr       */
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

	com.bit_index--;
	// Si todos los bits de un carácter han sido enviados, pasar al siguiente carácter
	if (com.bit_index < 0)
	{
		com.bit_index = 7;
		com.char_index++;
	}

}

void	handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
	{
		//Señal de confirmación de recepción de bit
		if (com.char_index < com.char_length)	//Checar si hay que checar esto si el server envía señal única al fianl
			send_current_bit_signal();
		
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
	if (DEBUG)
		ft_printf("Client starting bit-by-bit message sending ✉️\n");
	send_current_bit_signal();

	while (com.char_index < com.char_length)
		pause();
		
	return (0);
}

//make bonus CFLAGS+=" -DDEBUG=1"

//Unicode sample string: 😉ÆƠФڇ👍​




//TODO:
//comprobar orden de envio de bits y recepción en el servidor. Pq la última vez parece que el servidor no agrupó correctamente en bloques de 8
