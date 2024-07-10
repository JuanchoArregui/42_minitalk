/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:02:59 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:47:15 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

/* 
#ifndef MALLOC_FAIL
# define MALLOC_FAIL 0
#endif

void	*malloc(size_t n)
{
	static int	cnt = 0;

	if (cnt == MALLOC_FAIL)
		return (NULL);
	cnt++;
	return (calloc(n, 1));
}
*/

int	ft_printf(const char *text, ...)
{
	va_list	args;
	t_print	*struc;
	int		length;

	struc = (t_print *)malloc(sizeof(t_print));
	if (!struc)
		return (-1);
	if (!malloc_struc_variables(&struc, text))
		return (free(struc), -1);
	va_start(args, text);
	while (*text && !struc->error)
	{
		if (*text == '%')
			text = ft_txt_handle_pcnt(++text, &struc, args);
		else
			text = ft_txt_read_until_pcnt(text, &struc);
	}
	va_end(args);
	if (struc->error)
		return (-1);
	length = struc->length + ft_put_string(struc->print, struc->buff_position);
	free_struc(&struc);
	return (length);
}

int	malloc_struc_variables(t_print **struc, const char	*text)
{
	(*struc)->print = (char *)malloc(MAX_LENGTH * sizeof(char));
	if (!(*struc)->print)
		return (0);
	(*struc)->print[0] = '\0';
	(*struc)->copy_text = text;
	(*struc)->length = 0;
	(*struc)->buff_position = 0;
	(*struc)->error = 0;
	(*struc)->printf_str = (char *)malloc(MAX_LENGTH * sizeof(char));
	if (!(*struc)->printf_str)
		return (free((*struc)->print), 0);
	(*struc)->printf_len = 0;
	return (1);
}

void	free_struc(t_print **struc)
{
	free((*struc)->print);
	free((*struc)->printf_str);
	free((*struc));
}
