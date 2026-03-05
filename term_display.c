/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:20:19 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/05 13:01:38 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	ft_print_map(int map[MAP_SIZE][MAP_SIZE]);

// Possible to not work
void	ft_print_game_board(t_shm *shm, sem_t *sem)
{
	int	map_cpy[MAP_SIZE][MAP_SIZE];

	sem_wait(sem);
	ft_memcpy(map_cpy, shm->map, sizeof(shm->map));
	sem_post(sem);

	ft_print_map(map_cpy);
}

static void	ft_print_map(int map[MAP_SIZE][MAP_SIZE])
{
	printf("\033[%dA", MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		printf("\r\033[K");
		for (int j = 0; j < MAP_SIZE; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
}
