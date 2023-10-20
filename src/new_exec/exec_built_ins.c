/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:43:48 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/20 15:20:00 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(t_minishell *ms, char **cmd_arr)
{
	if (ft_strcmp(cmd_arr[0], "echo") == 0 || ft_strcmp(cmd_arr[0], "cd") == 0 \
		|| ft_strcmp(cmd_arr[0], "pwd") == 0 || ft_strcmp(cmd_arr[0], \
		"export") == 0 || ft_strcmp(cmd_arr[0], "unset") == 0 || \
		ft_strcmp(cmd_arr[0], "env") == 0 || ft_strcmp(cmd_arr[0], "exit") == 0)
	{
		built_ins(ms, cmd_arr, 0);
		return (1);
	}
	return (0);
}

void	exp_built_in(t_minishell *ms, char **cmd_arr)
{
	if (ft_strcmp(cmd_arr[0], "export") == 0) //Check if this makes sense
	{
		list_sort(ms->exp);
		if (export_error(cmd_arr))
		{
			g_exit = 1;
			return ;
		}
		if (arr_size(cmd_arr) > 1)
			export(cmd_arr, ms->exp, ms->env);
		else
			list_print(ms->exp);
	}
}

void	built_ins(t_minishell *ms, char **cmd_arr, int exit)
{
	if (ft_strcmp(cmd_arr[0], "echo") == 0)
		echo(cmd_arr);
	else if (ft_strcmp(cmd_arr[0], "cd") == 0)
		cd(ms, cmd_arr);
	else if (ft_strcmp(cmd_arr[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd_arr[0], "exit") == 0) //WRONG
	{
		if (exit) //WRONG
			write(STDERR_FILENO, "exit\n", 5);//WRONG
		ft_exit(ms, cmd_arr, exit);//WRONG
		if (exit) //WRONG
		{
			free_array(ms->paths);//WRONG
			free_ms(ms);//WRONG
		}
	}
	else if (ft_strcmp(cmd_arr[0], "env") == 0)
		list_print(ms->env);
	else if (ft_strcmp(cmd_arr[0], "unset") == 0)
		unset(ms->env, ms->exp, cmd_arr);
	else
		exp_built_in(ms, cmd_arr);
}