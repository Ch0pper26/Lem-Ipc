/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:49 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/30 16:06:11 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void	ft_init_player(t_player *player, int argc, char **argv)
{
	player->alive = true;
	player->first = false;
	if (argc == 4)
		player->team = ft_atoi(argv[argc - 3]);
	else
		player->team = -1;
	player->x = ft_atoi(argv[argc - 2]);
	player->y = ft_atoi(argv[argc - 1]);
}

t_shm	*ft_connect_shm(t_player *player, int *id)
{
	key_t	key;
	void	*mem;

	key = ftok("lem-ipc", 42);
	if (key == -1)
	{
		perror("Error : ");
		return (NULL);
	}

	*id = shmget(key, sizeof(t_shm), IPC_CREAT | IPC_EXCL | 0666);
	if (*id == -1)
	{
		*id = shmget(key, sizeof(t_shm), IPC_CREAT | 0666);
		if (*id == -1)
		{
			perror("Error : ");
			return (NULL);
		}
	}
	else
		player->first = true;

	mem = shmat(*id, NULL, 0);
	if (mem == (void *) -1)
	{
		perror("Error");
		if (player->first)
			shmctl(*id, IPC_RMID, NULL);
		return (NULL);
	}
	return (mem);
}

void	ft_init_shm(t_shm *shm, sem_t *sem)
{
	sem_wait(sem);
	shm->game_over = false;
	shm->nb_team = 0;
	for (int y = 0; y <= MAP_SIZE; y++)
	{
		for (int x = 0; x <= MAP_SIZE; x++)
		{
			shm->map[y][x] = 0;
		}
	}
	sem_post(sem);
}

sem_t	*ft_init_sem(t_player *player)
{
	sem_t	*sem;

	if (player->first)
		sem = sem_open("/access", O_CREAT, 0666, 1);
	else
		sem = sem_open("/access", 0);
	return (sem);
}
