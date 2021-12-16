/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:43 by cjang             #+#    #+#             */
/*   Updated: 2021/12/16 16:11:41 by cjang            ###   ########.fr       */
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

void	print_env(t_all *all);
void	set_env(char *key, char *value, t_all *all);
int		get_equl_idx(char *env);
char	*get_env_value(char *env, int len);
char	*get_env_key(char *env);
void	init_env(t_all *all, char **env);
#endif
