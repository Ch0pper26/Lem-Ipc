/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:47:04 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/24 13:27:34 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

/* *** *** *** --- INCUDES --- *** *** *** */

# include "Libft/ashes.h"
# include <stdbool.h>
# include <errno.h>
# include <ctype.h>
# include <limits.h>

/* *** *** *** --- DEFINES --- *** *** *** */

#ifndef MAP_SIZE
# define MAP_SIZE 30
#endif

# define LEFT -1
# define RIGHT 1
# define UP -1
# define DOWN 1

/* *** *** *** --- STRUCTURE --- *** *** *** */

typedef struct s_shm
{
	int	nb_team;
	int	map[MAP_SIZE][MAP_SIZE];
} t_shm;

typedef struct s_player
{
	int team;
	int	x;
	int y;
	bool alive;
} t_player;

/* *** *** *** --- ENUM --- *** *** *** */

enum { X, Y };

/* *** *** *** --- FUNCTIONS --- *** *** *** */

/* parsing.c */

bool	ft_parsing(int argc, char **argv);

/* init.c */
void	init_shm(t_shm *shm);

/* player.c */

void	ft_play(t_player *player);

inline bool ft_is_within_bound(int x, int y)
{
	// Use underflow to check < 0
	return (!((unsigned int) x >= MAP_SIZE || (unsigned int) y >= MAP_SIZE));
}

/* *** *** *** --- *** *** *** */

#endif
