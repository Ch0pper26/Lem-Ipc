/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:33 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/04 16:43:35 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

bool	g_stop_by_signal = false;

static void	ft_end(t_player *player, t_shm *shm, sem_t *sem, int id);
static void ft_handle_signal(int sig);

// TODO Maybe change display player by sending no argument or display argument
int main(int argc, char **argv)
{
	t_player	player;
	t_shm		*shm;
	sem_t		*sem;
	int			id;

	if (!ft_parsing(argc, argv))
		return (1);

	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);

	ft_init_player(&player, argc, argv);

	shm = ft_connect_shm(&player, &id);
	if (shm == NULL)
		return (1);

	sem = ft_init_sem(&player);
	if (sem == SEM_FAILED)
	{
		shmdt(shm);
		if (player.first)
			shmctl(id, IPC_RMID, NULL);
		perror("Error : ");
		return(1);
	}

	if (player.first)
		ft_init_shm(shm, sem);

	if (!ft_team_number(&player, shm, sem))
	{
		ft_end(&player, shm, sem, id);
		return (1);
	}

	if (player.first)
	{
		while (1)
		{
			if (g_stop_by_signal)
				break;
			sem_wait(sem);
			printf("%d\n", shm->nb_team);
			if (shm->nb_team == 5)
			{
				sem_post(sem);
				break;
			}
			sem_post(sem);
		}
	}

	ft_end(&player, shm, sem, id);

	return (0);
}

static void	ft_end(t_player *player, t_shm *shm, sem_t *sem, int id)
{
	shmdt(shm);
	sem_close(sem);
	if (player->first)
	{
		shmctl(id, IPC_RMID, NULL);
		sem_unlink("/access");
	}
}

static void ft_handle_signal(int sig)
{
	(void) sig;
	g_stop_by_signal = true;
}
