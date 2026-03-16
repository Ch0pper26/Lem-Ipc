/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:24:36 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/16 16:24:53 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static t_shm	*ft_create_shm(int *id);
static void		ft_init_shm(t_shm *shm, sem_t *sem);

int	ft_monitor(void)
{
	t_shm		*shm;
	sem_t		*sem;
	int			id;

	shm = ft_create_shm(&id);
	if (shm == NULL)
		return (1);

	sem = sem_open("/access", O_CREAT, 0666, 1);
	if (sem == SEM_FAILED)
	{
		perror("Error sem_open");
		shmdt(shm);
		shmctl(id, IPC_RMID, NULL);
		return (1);
	}

	ft_init_shm(shm, sem);

	while (!g_stop_by_signal)
	{
		ft_print_game_board(shm, sem);
		usleep(10000);
	}

	shmdt(shm);
	sem_close(sem);
	shmctl(id, IPC_RMID, NULL);
	sem_unlink("/access");

	return (0);
}

static t_shm	*ft_create_shm(int *id)
{
	key_t	key;
	void	*mem;

	key = ftok("lem-ipc", 42);
	if (key == -1)
	{
		perror("Error ftok");
		return (NULL);
	}

	*id = shmget(key, sizeof(t_shm), IPC_CREAT | IPC_EXCL | 0666);
	if (*id == -1)
	{
		perror("Error shmget");
		return (NULL);
	}

	mem = shmat(*id, NULL, 0);
	if (mem == (void *) -1)
	{
		perror("Error shmat");
		shmctl(*id, IPC_RMID, NULL);
		return (NULL);
	}

	return (mem);
}

static void	ft_init_shm(t_shm *shm, sem_t *sem)
{
	sem_wait(sem);
	shm->game_over = false;
	shm->nb_team = 0;
	for (int y = 0; y <= MAP_SIZE; y++)
	{
		for (int x = 0; x <= MAP_SIZE; x++)
			shm->map[y][x] = 0;
	}
	sem_post(sem);
}
