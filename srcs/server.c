/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:33 by jarregui          #+#    #+#             */
/*   Updated: 2024/12/02 19:56:55 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


//TODO: revisar como se imprime la lista pq solo me imprime un caracter



t_msg_list	g_msg_list; //la lista está definida como variable global
//Mirar codigo de: https://github.com/blasdo/minitalk/blob/main/server.c

void	print_and_clear_msg_list(t_msg_list *lst)
{
	t_msg_list *current;
	t_msg_list *next_node;

	if (DEBUG)
	{
		write(1, "\n✅ TERMINADA TRANSMISION:", 24);
		write(1, "\nESTE ES EL MENSAJE RECIBIDO:\n", 31);
	}
	current = lst->next;
	write(1, &lst->ch, 1);
	lst->ch = 0;
	lst->next = NULL;
	while (current)
	{
		if (current->ch != '\0')
			write(1, &current->ch, 1); // Imprime cada carácter
		next_node = current->next; // Guarda el siguiente nodo
		free(current); // Libera el nodo actual
		current = next_node; // Pasa al siguiente nodo
	}
	write(1, "\n", 1); // Salto de línea
}

void	ft_msg_list_add_char(t_msg_list *lst, char ch)
{
	t_msg_list	*new_char;

	if (!lst->ch)
		lst->ch = ch;
	else
	{
		new_char = malloc(sizeof(t_msg_list));
		new_char->ch = ch;
		new_char->next = NULL;
		while (lst->next)
			lst = (lst)->next;	// Avanzas al siguiente nodo
		lst->next = new_char;	// Añades el nuevo nodo al final
	}
	if (ch == END_TRANSMISSION)
		print_and_clear_msg_list(lst);
}

void	print_bit_signal(int bit_index, int signal)
{
	if (DEBUG)
	{
		if (bit_index == 0)
			write(1, "\n", 1);
		if (signal == SIGUSR1)
			write(1, "1", 1);
		else if (signal == SIGUSR2)
			write(1, "0", 1);
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
		if (DEBUG)
		{
			write(1, " - ", 3);
			write(1, &current_char, 1);
		}
		//añadimos current_char a la lista:
		ft_msg_list_add_char(&g_msg_list, current_char);

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
	g_msg_list.ch = '\0';
	g_msg_list.next = NULL;
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	if (DEBUG)
		ft_printf("Server is Listening...\n");
	while (1)
		pause();
	return (0);
}

//make CFLAGS+=" -DDEBUG=1"
//Info sobre minitalk:  
//https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24
//
//https://github.com/hanshazairi/42-minitalk
//https://github.com/leogaudin/minitalk/tree/main
