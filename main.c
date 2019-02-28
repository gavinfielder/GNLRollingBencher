/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:52:04 by gfielder          #+#    #+#             */
/*   Updated: 2019/02/23 00:31:27 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filegen.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int test_num = 0;
	int min_tests = 0;
	int max_tests = 20;
	if (argc > 2)
	{
		max_tests = atoi(argv[2]);
		min_tests = atoi(argv[1]);
	}
	char filename[64];
	test_num = min_tests;
	while (test_num < max_tests)
	{
		sprintf(filename, "tests/test_%i.txt", test_num);
		if (generate_file(filename) != FILEGEN_OK)
			printf("There was an error while generating %s.\n", filename);
		test_num++;
	}
	return (0);
}
