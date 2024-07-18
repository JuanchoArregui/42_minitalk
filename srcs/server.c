/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/18 16:34:57 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_bit_signal(int bit_index, int signal)
{
	if (DEBUG)
	{
		if (bit_index == 0)
			write(1, "\n", 1);
		if (signal == SIGUSR1)
			write(1, "0", 1);
		else if (signal == SIGUSR2)
			write(1, "1", 1);
	}
}

void	handle_signal(int signal)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;

	print_bit_signal(bit_index, signal);
	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
			write(1, "\n", 1);
		else
		{
			if (DEBUG)
				write(1, " - ", 3);
			write(1, &current_char, 1);
		}
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	if (DEBUG)
		ft_printf("PID: ");
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	if (DEBUG)
		ft_printf("Server is Listening...\n");
	while (1)
		pause();
	return (0);
}

//Info sobre minitalk:  
//https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24
//
//https://github.com/hanshazairi/42-minitalk
//https://github.com/leogaudin/minitalk/tree/main
