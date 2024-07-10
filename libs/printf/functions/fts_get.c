/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:34:53 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:47:21 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

char	*ft_get_basechars(char base_type)
{
	if (base_type == 'X')
		return ("0123456789ABCDEF");
	else if (base_type == 'x')
		return ("0123456789abcdef");
	else
		return ("0123456789");
}

int	ft_get_base(char base_type)
{
	if (base_type == 'X')
		return (16);
	else if (base_type == 'x')
		return (16);
	else
		return (10);
}
