/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:09:58 by gfielder          #+#    #+#             */
/*   Updated: 2019/02/23 00:42:20 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filegen.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

static int		random_int(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}
static void	write_random_printable_ascii(int fd, int *bytes, char *last_written)
{
	char c = (char)random_int(32, 126);
	write(fd, &c, 1);
	*last_written = c;
	bytes++;
}

static void	write_random_byte(int fd, int *nonprintables, int *bytes, int *null_terminators, char *last_written)
{
	char c = (char)random_int(0, 255);
	write(fd, &c, 1);
	*last_written = c;
	if (!(c >= 32 && c <= 126))
		(*nonprintables)++;
	if (c == '\0')
		(*null_terminators)++;
	(*bytes)++;
}

static void	write_newline(int fd, int *newlines, int *bytes, int *nonprintables, char *last_written)
{
	write(fd, "\n", 1);
	*last_written = '\n';
	(*newlines)++;
	(*bytes)++;
	//(*nonprintables)++;
}

/*
** #--------------------------------------------------------------------#
** |                        Probability Table							|
** #--------------------------------------------------------------------#
** |   print a random printable ascii char			r	<=	ptab[0]		|
** |   print a newline								r	<=	ptab[1]		|
** |   print a random byte							r	<=	ptab[2]		|
** |   finish writing the file						r	<=	ptab[3]		|
** |   chance (out of 100) that \n is last char				ptab[4]		|
** #--------------------------------------------------------------------#
*/

int generate_file(char *filename)
{

	int				newlines = 0;
	int				bytes = 0;
	int				nonprintables = 0;
	int				null_terminators = 0;
	char			last_written = 'a';
	int				fd_info;
	char			*info_filename;

	static int initialized = 0;
	if (!(initialized))
	{
		srand(time(0));
		initialized = 1;
	}

	int	ptab[5];
	ptab[0] = random_int(-20000, 100000);	//random printable ascii char
	if (ptab[0] < 0) ptab[0] = random_int(0, 5000);
	ptab[1] = random_int(-1000, 5000); 		//newline
	if (ptab[1] < 0) ptab[1] = random_int(0, 700);
	ptab[2] = random_int(0, 2000);		//random byte
	ptab[3] = random_int(1, 300);	//eof
	ptab[4] = random_int(50, 100);		//file ends with \n

	int	ptab_div = ptab[0] + ptab[1] + ptab[2] + ptab[3];
	ptab[1] += ptab[0];
	ptab[2] += ptab[1];
	ptab[3] += ptab[2];

	int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC,  S_IRWXU | S_IRWXG | S_IRWXO);
	int	r = 0;
	while (fd > 0)
	{
		r = random_int(0, ptab_div);
		if (r <= ptab[0])
			write_random_printable_ascii(fd, &bytes, &last_written);
		else if (r <= ptab[1])
			write_newline(fd, &newlines, &bytes, &nonprintables, &last_written);
		else if (r <= ptab[2])
			write_random_byte(fd, &nonprintables, &bytes, &null_terminators, &last_written);
		else
		{
			//eof
			r = random_int(0, 100);
			if (r <= ptab[4])
			{
				write(fd, "\n", 1);
				last_written = '\n';
				bytes++;
				//nonprintables++;
			}
			close(fd);
			//write information about the file to [filename].info
			info_filename = ft_strjoin(filename, ".info");
			fd_info = open(info_filename, O_CREAT | O_WRONLY | O_TRUNC,  S_IRWXU | S_IRWXG | S_IRWXO);
			if (fd_info > 0)
			{
				dprintf(fd_info, "filename          %s\n", filename);
				dprintf(fd_info, "bytes             %i\n", bytes);
				dprintf(fd_info, "newlines          %i\n", newlines);
				dprintf(fd_info, "nonprintables     %i\n", nonprintables);
				dprintf(fd_info, "null terminators  %i\n", null_terminators);
				dprintf(fd_info, "ends with \\n     %s\n", (last_written == '\n' ? "YES" : "NO"));
				dprintf(fd_info, "ends with ascii   %#x\n", last_written);
				close(fd_info);
			}
			free(info_filename);
			fd = FILEGEN_OK;
		}
	}
	return (fd);
}
