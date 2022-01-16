/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:46:23 by cjang             #+#    #+#             */
/*   Updated: 2022/01/17 01:26:01 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>

/* std_backup */
void		std_save(int *stdin, int *stdout, int *stderr);
void		std_restore(int stdin, int stdout, int stderr);

/* redirection */
int			heredoc_tmp_file_delete(int tmp_count);
#endif
