/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:03:40 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/04 16:43:32 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void ft_check_start(t_player *player, t_shm *shm, sem_t *sem);
static bool	ft_move(int map[MAP_SIZE][MAP_SIZE], t_player *player, int move[2]);
static void	ft_check_death(t_shm *shm, t_player *player);
extern inline bool	ft_is_within_bound(int x, int y);

// TODO Win
// TODO Launch Game
void	ft_play(t_player *player, t_shm *shm, sem_t *sem)
{
	int		move[2];

	ft_check_start(player, shm, sem);
	while (player->alive)
	{
		sem_wait(sem);
		ft_check_death(shm, player);
		if (!player->alive)
		{
			shm->map[player->y][player->x] = 0;
			sem_post(sem);
			return ;
		}

		// ft_choose_direction
		move[X] = 0;
		move[Y] = 0;
		ft_move(shm->map, player, move);
		sem_post(sem);
	}
}

static void ft_check_start(t_player *player, t_shm *shm, sem_t *sem)
{
	sem_wait(sem);
	if (shm->map[player->y][player->x] != 0)
	{
		ft_print_error("There is already a player at these coordinates");
		player->alive = false;
	}
	else
		shm->map[player->y][player->x] = player->team;
	sem_post(sem);
}

static void	ft_check_death(t_shm *shm, t_player *player)
{
	static int	nb_team;
	static int	*enemies_count;
	int			y_to_check;
	int			x_to_check;

	if (enemies_count == NULL || shm->nb_team != nb_team)
	{
		nb_team = shm->nb_team;
		int	*tmp = realloc(enemies_count, sizeof(int) * (nb_team - 1));

		if (tmp == NULL)
		{
			free(enemies_count);
			player->alive = false;
		}
		else
			enemies_count = tmp;
	}

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			if (y == 0 && x == 0)
				continue ;

			y_to_check = player->y + y;
			x_to_check = player->x + x;
			if ((unsigned int) y_to_check >= MAP_SIZE
				|| (unsigned int) x_to_check >= MAP_SIZE)
				continue ;

			if (shm->map[y_to_check][x_to_check] != 0
					&& shm->map[y_to_check][x_to_check] != player->team)
				(enemies_count[shm->map[y_to_check][x_to_check]])++;
		}
	}

	for (int team = 0; team <= nb_team; team++)
	{
		if (enemies_count[team] >= 2)
		{
			player->alive = false;
			free(enemies_count);
		}
	}
}

static bool	ft_move(int map[MAP_SIZE][MAP_SIZE], t_player *player, int move[2])
{
	int	next_x;
	int	next_y;

	next_x = player->x + move[X];
	next_y = player->y + move[Y];

	if (!ft_is_within_bound(next_x, next_y))
		return (false);

	if (map[next_y][next_x] != 0)
		return (false);

	player->x = next_x;
	player->y = next_y;

	return (true);
}
