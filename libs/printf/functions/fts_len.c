/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:28:40 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:47:36 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

int	ft_len_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_len_int(int nb, char c)
{
	t_len_int	len_int;

	if (!nb)
		return (1);
	set_neg_pos(nb, &len_int);
	if (c == 'i' || c == 'd')
	{
		while (len_int.number)
		{
			len_int.number /= 10;
			len_int.i++;
		}
	}
	else if (c == 'x')
	{
		while (len_int.number)
		{
			len_int.number /= 16;
			len_int.i++;
		}
	}
	else
		return (0);
	return (len_int.i + len_int.neg);
}

void	set_neg_pos(int nb, t_len_int *len_int)
{
	len_int->i = 0;
	if (nb < 0)
	{
		len_int->neg = 1;
		len_int->number = -nb;
	}
	else
	{
		len_int->neg = 0;
		len_int->number = nb;
	}
}
