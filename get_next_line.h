/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:18:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2023/11/01 07:09:38 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
#if BUFFER_SIZE < 0
#define BUFFER_SIZE 0
#endif 

char *get_next_line(int fd);

#endif