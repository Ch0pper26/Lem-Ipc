/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:47:06 by eblondee          #+#    #+#             */
/*   Updated: 2025/11/19 10:47:09 by eblondee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

char	*get_next_line(int fd);
char	*ft_strjoin_free(char const *s1, char const *s2);
int		ft_find_bsn(char *str);
char	*ft_read(int fd, char *buffer);
char	*ft_new_buffer(char *buffer);
char	*ft_recup_line(char *buffer);

#endif
