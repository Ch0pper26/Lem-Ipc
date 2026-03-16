/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:03:40 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/16 16:28:02 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static bool	ft_move(int map[MAP_SIZE][MAP_SIZE], t_player *player, int move[2]);
static void	ft_check_death(t_shm *shm, t_player *player);
extern inline bool	ft_is_within_bound(int x, int y);

// TODO Win
// TODO Launch Game
void	ft_play(t_player *player, t_shm *shm, sem_t *sem)
{
	int		move[2];

	sem_wait(sem);
	shm->map[player->y][player->x] = player->team;
	sem_post(sem);

	while (!g_stop_by_signal)
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
		move[X] = 1;
		move[Y] = 1;
		ft_move(shm->map, player, move);
		sem_post(sem);

		sleep(3);
	}

	sem_wait(sem);
	shm->map[player->y][player->x] = 0;
	sem_post(sem);
}

// TODO If surround by 3 player from different team what do we do ??
static void	ft_check_death(t_shm *shm, t_player *player)
{
	int	enemies_count[shm->nb_team];
	int	y_to_check;
	int	x_to_check;

	ft_memset(enemies_count, 0, sizeof(int) * shm->nb_team);

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

	for (int team = 0; team < shm->nb_team; team++)
		if (enemies_count[team] >= 2)
			player->alive = false;
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

	map[player->y][player->x] = 0;
	player->x = next_x;
	player->y = next_y;
	map[player->y][player->x] = player->team;

	return (true);
}
