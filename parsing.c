/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:29:56 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/24 13:27:44 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static bool	ft_is_uint(char *str)
{
	char *endptr;
	unsigned long val;

	if (str == NULL || *str == '\0')
		return (false);
	while (isspace(*str))
		str++;
	if (*str == '-')
		return (false);

	errno = 0; 
	val = strtoul(str, &endptr, 10);
	if (str == endptr)
		return (false);

	if (*endptr != '\0')
		return (false);

	if (errno == ERANGE)
		return (false);

	if (val > UINT_MAX)
		return (false);

    return (true);
}

#include <stdio.h>

// TODO pass the shm segment
bool	ft_parsing(int argc, char **argv)
{
	if (argc > 4)
	{
		ft_print_error("Too many arguments given");
		return (false);
	}

	if (argc <= 2)
	{
		ft_putstr_fd("Usage : ./lem-ipc [<team's number>] <coord_x> <coord_y>\n", 1);
		return (false);
	}

	if (!ft_is_uint(argv[1]) || !ft_is_uint(argv[2])
		|| (argc == 4 && !ft_is_uint(argv[3])))
	{
		ft_print_error("One of the arguments is not a positive Int");
		return (false);
	}

	unsigned int x;
	unsigned int y;

	x = strtoul(argv[argc - 1], NULL, 10);
	y = strtoul(argv[argc - 2], NULL, 10);

	if (x >= INT_MAX || y >= INT_MAX)
	{
		ft_print_error("One of the arguments is not an positive Int");
		return (false);
	}

	if (!ft_is_within_bound(x, y))
	{
		ft_print_error("Coord outside of the map");
		return (false);
	}

	// TODO Check team number

	return (true);
}
