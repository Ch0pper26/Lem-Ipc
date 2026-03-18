/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:33 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/18 15:33:13 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

bool	g_stop_by_signal = false;

static void	ft_end(t_shm *shm, sem_t *sem);
static void	ft_handle_signal(int sig);

// TODO Maybe add color team in parameter
// TODO Maybe undo lem_ipc display separation
int	main(int argc, char **argv)
{
	t_player	player;
	t_shm		*shm;
	sem_t		*sem;

	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);

	if (argc == 1)
		return (ft_monitor());

	if (!ft_parsing(argc, argv))
		return (1);

	ft_init_player(&player, argc, argv);

	shm = ft_connect_shm();
	if (shm == NULL)
		return (1);

	sem = sem_open("/access", 0);
	if (sem == SEM_FAILED)
	{
		perror("Error sem_open");
		shmdt(shm);
		return (1);
	}

	if (!ft_team_number(&player, shm, sem))
	{
		ft_end(shm, sem);
		return (1);
	}

	ft_handle_play(&player, shm, sem);
	ft_end(shm, sem);

	return (0);
}

static void	ft_handle_signal(int sig)
{
	(void) sig;
	g_stop_by_signal = true;
}

static void	ft_end(t_shm *shm, sem_t *sem)
{
	shmdt(shm);
	sem_close(sem);
}
