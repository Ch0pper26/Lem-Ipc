/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:03:40 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/18 16:03:19 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static bool	ft_game_start(t_shm *shm, sem_t *sem);
static void	ft_play(t_player *player, t_shm *shm, sem_t *sem);
static bool	ft_move(int map[MAP_SIZE][MAP_SIZE], t_player *player, int move[2]);
static void	ft_check_death(t_shm *shm, t_player *player);
extern inline bool	ft_is_within_bound(int x, int y);

// TODO Win
// TODO Launch Game
void	ft_handle_play(t_player *player, t_shm *shm, sem_t *sem)
{

	sem_wait(sem);
	shm->map[player->y][player->x] = player->team;
	sem_post(sem);

	while(!ft_game_start(shm, sem) && !g_stop_by_signal)
		continue;

	sleep(1);
	ft_play(player, shm, sem);
	
	if (g_stop_by_signal)
	{
		sem_wait(sem);
		shm->map[player->y][player->x] = 0;
		shm->teams[player->team] -= 1;
		sem_post(sem);
	}
}

static bool	ft_game_start(t_shm *shm, sem_t *sem)
{
	int nb_team_ready;

	nb_team_ready = 0;
	sem_wait(sem);
	if (shm->game_over == false)
	{
		sem_post(sem);
		return (true);
	}

	if (shm->nb_team < NB_TEAM_TO_PLAY)
	{
		sem_post(sem);
		return(false);
	}

	for (int i = 1; i <= shm->nb_team; i++)
		if (shm->teams[i] >= NB_PLAYER_IN_TEAM)
			nb_team_ready++;

	if (nb_team_ready != shm->nb_team)
	{
		sem_post(sem);
		return(false);
	}
	sem_post(sem);

	return (true);
}

static void	ft_play(t_player *player, t_shm *shm, sem_t *sem)
{
	int		move[2];

	while (!g_stop_by_signal)
	{
		sem_wait(sem);
		ft_check_death(shm, player);
		if (!player->alive)
		{
			shm->map[player->y][player->x] = 0;
			shm->teams[player->team] -= 1;
			sem_post(sem);
			return ;
		}

		// ft_choose_direction
		move[X] = 1;
		move[Y] = 1;
		ft_move(shm->map, player, move);
		sem_post(sem);

		sleep(2);
	}
}

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
