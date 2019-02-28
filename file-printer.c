/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 23:24:13 by gfielder          #+#    #+#             */
/*   Updated: 2019/02/22 23:48:11 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int				get_next_line(const int fd, char **line);

int				main(int argc, char **argv)
{
	int			i;
	int			fd;
	int			ret;
	char		*line;

	if (argc == 2)
	{
		i = 0;
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			ret = get_next_line(fd, &line);
			if (ret == 1)
			{
				printf("|<|%s|>|, %i\n", line, ret);
				free(line);
			}
			else
			{
				printf(", %i\n", ret);
				break ;
			}
		}
		close(fd);
	}
	return (0);
}
