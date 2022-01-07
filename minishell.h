/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:43 by cjang             #+#    #+#             */
/*   Updated: 2022/01/07 14:45:05 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
// # include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_env_lst
{
	t_env			*head;
	int				num_env;
}t_env_lst;

typedef struct s_all
{
	t_env_lst		*env;
}t_all;

/* init_env */
void	init_env(t_all *all, char **env);

/* env_func */
char	*find_env_key(t_all *all, char *key);
void	delete_env_key(t_all *all, char *key);

/* utils */
size_t	ft_strlen_long(const char *s1, const char *s2);
int		ft_is_fd_range(char *s, int s_len);
#endif
