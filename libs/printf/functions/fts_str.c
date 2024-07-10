/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:21:11 by jarregui          #+#    #+#             */
/*   Updated: 2024/03/11 18:35:47 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

int	ft_strcpy(const char *src, char *dst, size_t dst_start)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && dst_start + i < MAX_LENGTH)
	{
		dst[dst_start + i] = src[i];
		++i;
	}
	dst[dst_start + i] = '\0';
	return (dst_start + i);
}

int	ft_strcpy_size(const char *src, char *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (i);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		++i;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

int	ft_strcmp_size(const char *str1, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str1[i] != str2[i])
			return (0);
		++i;
	}
	if (str1[size] == '\0' && str2[size] == '\0')
		return (1);
	return (0);
}

size_t	ft_strlncpy(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	i;

	length = 0;
	i = 0;
	while (src[length] != '\0')
		++length;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (length);
}
