/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:33 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/21 16:53:38 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_shm	test;

	init_shm(&test);
	ft_printf("%i", test.map[0][0]);
	ft_printf("%i", test.map[29][29]);

	return (0);
}
