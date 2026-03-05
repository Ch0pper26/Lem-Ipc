/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:49 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/05 14:36:49 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void	ft_init_player(t_player *player, int argc, char **argv)
{
	player->alive = true;
	if (argc == 4)
		player->team = ft_atoi(argv[argc - 3]);
	else
		player->team = -1;
	player->x = ft_atoi(argv[argc - 2]);
	player->y = ft_atoi(argv[argc - 1]);
}

t_shm	*ft_connect_shm(void)
{
	int		id;
	key_t	key;
	void	*mem;

	key = ftok("lem-ipc", 42);
	if (key == -1)
	{
		perror("Error ftok");
		return (NULL);
	}

	id = shmget(key, sizeof(t_shm), 0666);
	if (id == -1)
	{
		perror("Error shmget");
		return (NULL);
	}

	mem = shmat(id, NULL, 0);
	if (mem == (void *) -1)
	{
		perror("Error shmat");
		return (NULL);
	}
	return (mem);
}
