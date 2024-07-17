/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:11:51 by jarregui          #+#    #+#             */
/*   Updated: 2024/07/17 16:32:44 by jarregui         ###   ########.fr       */
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

#define MICROSECS 42
#define END_TRANSMISSION '\0'

#endif