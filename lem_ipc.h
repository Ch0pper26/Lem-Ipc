/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:47:04 by eblondee          #+#    #+#             */
/*   Updated: 2026/03/18 15:44:01 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

/* *** *** *** --- INCLUDES --- *** *** *** */

# include "Libft/ashes.h"

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/ipc.h>
# include <sys/shm.h>

/* *** *** *** --- DEFINES --- *** *** *** */

#ifndef MAP_SIZE
# define MAP_SIZE 25
#endif

#ifndef MAX_TEAM
# define MAX_TEAM 230
#endif

// TODO Put real number
#ifndef NB_TEAM_TO_PLAY
# define NB_TEAM_TO_PLAY 2
#endif

// TODO Put real number
#ifndef NB_PLAYER_IN_TEAM
# define NB_PLAYER_IN_TEAM 1
#endif

# define LEFT -1
# define RIGHT 1
# define UP -1
# define DOWN 1


/* *** *** *** --- GLOBALS --- *** *** *** */

extern bool	g_stop_by_signal;

/* *** *** *** --- STRUCTURES --- *** *** *** */

typedef struct s_shm
{
	bool	game_over;
	int		nb_team;
	int		map[MAP_SIZE][MAP_SIZE];
	int		teams[MAX_TEAM];
}	t_shm;

typedef struct s_player
{
	bool	alive;
	int		team;
	int		x;
	int		y;
}	t_player;

/* *** *** *** --- ENUM --- *** *** *** */

enum { X, Y };

/* *** *** *** --- FUNCTIONS --- *** *** *** */

/* monitor.c */
int		ft_monitor(void);

/* parsing.c */

bool	ft_parsing(int argc, char **argv);
bool	ft_team_number(t_player *player, t_shm *shm, sem_t *sem);

/* init.c */

void	ft_init_player(t_player *player, int argc, char **argv);
t_shm	*ft_connect_shm(void);

/* term_display.c */
void	ft_print_game_board(t_shm *shm, sem_t *sem);

/* player.c */

void	ft_handle_play(t_player *player, t_shm *shm, sem_t *sem);

inline bool	ft_is_within_bound(int x, int y)
{
	// Use underflow to check < 0
	return (!((unsigned int) x >= MAP_SIZE || (unsigned int) y >= MAP_SIZE));
}

/* *** *** *** --- *** *** *** */

#endif
