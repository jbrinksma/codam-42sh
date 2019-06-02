/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh_history.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 17:42:22 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/30 21:01:33 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_HISTORY_H
# define VSH_HISTORY_H

int		history_i;
char	**history;

int				history_to_file(void);
int				history_get_file_content(void);
int				history_line_to_array(char *line);
void			history_print(void);

#endif