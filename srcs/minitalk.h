/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:11:51 by jarregui          #+#    #+#             */
/*   Updated: 2024/08/22 13:04:07 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libs/libft/libft.h"
# include "../libs/printf/printf.h"

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#define MICROSECS 100
#define END_TRANSMISSION '\0'

typedef struct s_com_state
{
	char			*message;
	pid_t			server_pid;
	int				server_checked;
	int				char_length;
	int				char_index;
	unsigned char	temp_char;
	int				bit_index;
}	t_com_state;

#endif