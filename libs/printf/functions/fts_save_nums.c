/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_save_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:34:53 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:47:55 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

void	ft_save_pointer(void *ptr, t_print **struc)
{
	unsigned long	ptr_address;

	if (ptr == NULL)
	{
		ft_save_string("0x0", struc);
	}
	else
	{
		ft_save_string("0x", struc);
		ptr_address = (unsigned long)ptr;
		ft_save_u_long(ptr_address, 'x', struc);
	}
}

void	ft_save_num_base(long int nb, char base_type, t_print **struc)
{
	char			*basechars;
	int				base;
	int				res[100];
	int				i;

	if (nb < 0)
	{
		ft_save_char('-', struc);
		nb = -1 * nb;
	}
	basechars = ft_get_basechars(base_type);
	base = ft_get_base(base_type);
	i = 0;
	while (nb >= base)
	{
		res[i] = basechars[nb % base];
		nb /= base;
		i++;
	}
	res[i] = basechars[nb];
	while (i >= 0)
	{
		ft_save_char(res[i], struc);
		i--;
	}
}

void	ft_save_u_long(unsigned long nb, char base_type, t_print **struc)
{
	char		*basechars;
	int			res[100];
	int			i;

	basechars = ft_get_basechars(base_type);
	i = 0;
	while (nb >= 16)
	{
		res[i] = basechars[nb % 16];
		nb /= 16;
		i++;
	}
	res[i] = basechars[nb];
	while (i >= 0)
	{
		ft_save_char(res[i], struc);
		i--;
	}
}
