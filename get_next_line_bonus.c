/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:51:00 by owatanab          #+#    #+#             */
/*   Updated: 2023/11/06 17:58:40 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *s1, char *s2, ssize_t l2);
int		check_new_line(char **s, char **line, ssize_t max);
char	*buf_read(char **buf, int fd, char **rest);

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*rest[1024];

	line = NULL;
	if (BUFFER_SIZE <= 0 || (rest[fd]
			&& *(rest[fd]) && check_new_line(&rest[fd], &line, -1) == 0))
		return (line);
	free(rest[fd]);
	rest[fd] = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(line);
		return (NULL);
	}
	line = concat(line, buf_read(&buf, fd, &rest[fd]), -1);
	free(buf);
	return (line);
}
