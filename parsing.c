/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:29:56 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/05 14:47:37 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static bool	ft_is_uint(char *str)
{
	char			*endptr;
	unsigned long	val;

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

	while (isspace(*endptr))
		endptr++;

	if (*endptr != '\0')
		return (false);

	if (errno == ERANGE)
		return (false);

	if (val > UINT_MAX)
		return (false);

	return (true);
}

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

	unsigned int	y;
	unsigned int	x;
	unsigned int	team;

	y = strtoul(argv[argc - 1], NULL, 10);
	x = strtoul(argv[argc - 2], NULL, 10);

	team = strtoul(argv[argc - 3], NULL, 10);

	if (x > INT_MAX || y > INT_MAX || (argc == 4 && team > INT_MAX))
	{
		ft_print_error("One of the arguments is not an positive Int");
		return (false);
	}

	if (!ft_is_within_bound(x, y))
	{
		ft_print_error("Coord outside of the map");
		return (false);
	}

	return (true);
}

bool	ft_team_number(t_player *player, t_shm *shm, sem_t *sem)
{
	sem_wait(sem);

	if (shm->map[player->y][player->x] != 0)
	{
		ft_print_error("There is already a player at these coordinates");
		player->alive = false;
		sem_post(sem);
		return (false);
	}

	if (player->team == -1)
	{
		shm->nb_team++;
		player->team = shm->nb_team;
	}

	if (shm->nb_team == 0)
	{
		if (player->team != 1)
		{
			fprintf(stderr, "\x1b[38;5;203mError :\nWrong team number, the only one possible is 1\n\x1b[0m");
			sem_post(sem);
			return (false);
		}
		else
			shm->nb_team++;
	}

	if (player->team > shm->nb_team || player->team <= 0)
	{
		fprintf(stderr, "\x1b[38;5;203mError :\nWrong team number, the only one possible are beetwen 1-%d\n\x1b[0m", shm->nb_team);
		sem_post(sem);
		return (false);
	}
	sem_post(sem);
	return (true);
}
