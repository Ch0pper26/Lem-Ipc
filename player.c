/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:03:40 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/24 13:28:02 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static bool	ft_move(int **map, t_player *player, int move[2]);
static void	ft_check_death(int **map, t_player *player);

extern inline bool ft_is_within_bound(int x, int y);

// TODO Finish it
void ft_play(t_player *player)
{
	int **map;
	int move[2];

	map = NULL;
	while (player->alive)
	{
		// lock
		ft_check_death(map, player);
		
		if (!player->alive)
			// delock
			return ;

		// ft_choose_direction
		ft_move(map, player, move);
		// delock
	}
}

static void	ft_check_death(int **map, t_player *player)
{
	int	*enemies_count;
	int	y_to_check;
	int	x_to_check;

	// TODO malloc it
	// make it static and reallocating it only when neccessary ??
	enemies_count = NULL;	
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			if (y == 0 && x == 0)
				continue;
		
			y_to_check = player->y + y;
				x_to_check = player->x + x;
	
			if ((unsigned int) y_to_check >= MAP_SIZE
				|| (unsigned int) x_to_check >= MAP_SIZE)
				continue;

			if (map[y_to_check][x_to_check] != 0
					&& map[y_to_check][x_to_check] != player->team)
				enemies_count[map[y_to_check][x_to_check]]++;
		}
	}

	// TODO Check in tab
	if (*enemies_count >= 2)
		player->alive = false;
}

static bool	ft_move(int **map, t_player *player, int move[2])
{
	int	next_x;
	int	next_y;

	next_x = player->x + move[X];
	next_y = player->y + move[Y];

	if (!ft_is_within_bound(next_x, next_y))
		return (false);

	/* Check if will not move to an other player */
	if (map[next_y][next_x] != 0)
		return (false);

	player->x = next_x;
	player->y = next_y;

	return (true);
}
