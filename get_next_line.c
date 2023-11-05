/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:17:50 by otawatanabe       #+#    #+#             */
/*   Updated: 2023/11/05 10:46:05 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *s1, char *s2, ssize_t l2);
int		check_new_line(char *s, char **line, ssize_t max);
char	*buf_read(char **buf, int fd, char **rest);

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*rest;

	line = NULL;
	if (BUFFER_SIZE <= 0
		|| (rest && *rest && check_new_line(rest, &line, -1) == 0))
		return (line);
	free(rest);
	rest = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(line);
		return (NULL);
	}
	line = concat(line, buf_read(&buf, fd, &rest), -1);
	free(buf);
	return (line);
}
