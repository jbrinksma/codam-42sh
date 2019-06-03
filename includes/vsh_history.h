/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh_history.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 17:42:22 by mavan-he       #+#    #+#                */
/*   Updated: 2019/06/02 15:12:20 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_HISTORY_H
# define VSH_HISTORY_H

int		history_i;
int		history_tmp;
char	**history;

#define ARROW_UP 1
#define ARROW_DOWN 2

int				history_to_file(void);
int				history_get_file_content(void);
int				history_line_to_array(char *line);
void			history_print(void);
void			history_change_line(char **line, unsigned *index, char arrow);

#endif