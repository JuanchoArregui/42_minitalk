/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_handling_main_txt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:21:11 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:47:30 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

const char	*ft_txt_handle_pcnt(const char *text, t_print **struc, va_list args)
{
	if (*text == 'c')
		ft_save_char(va_arg(args, int), struc);
	else if (*text == 's')
		ft_save_string(va_arg(args, char *), struc);
	else if (*text == 'p')
		ft_save_pointer(va_arg(args, void *), struc);
	else if (*text == 'd')
		ft_save_num_base(va_arg(args, int), 'd', struc);
	else if (*text == 'i')
		ft_save_num_base(va_arg(args, int), 'i', struc);
	else if (*text == 'u')
		ft_save_num_base(va_arg(args, unsigned int), 'u', struc);
	else if (*text == 'x')
		ft_save_num_base(va_arg(args, unsigned int), 'x', struc);
	else if (*text == 'X')
		ft_save_num_base(va_arg(args, unsigned int), 'X', struc);
	else if (*text == '%')
		ft_save_char('%', struc);
	else
		return (((*struc)->error = 1), text);
	return (++text);
}

const char	*ft_txt_read_until_pcnt(const char *text, t_print **struc)
{
	while (*text)
	{
		if (*text == '%')
			return ((char *)text);
		ft_save_char(*text, struc);
		text++;
	}
	return ((char *)text);
}
