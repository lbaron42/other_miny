/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_2.c: 1.	*/

static int	check_cd_errors(char *str, char *cd, int i)
{
	if ((!cd[0]) || (cd[0] == '.' && !cd[1]))
	{
		printf("minishell: cd: only relative or absolute paths are supported\n");
		return (ft_return(1, 0));
	}
	else if ((cd[0] == '.' && cd[1] == '.') || (cd[0] == '-' && !cd[1]))
	{
		printf("minishell: cd: only relative or absolute paths are supported\n");
		return (ft_return(1, 0));
	}
	else if (!empty_check(str, i))
	{
		printf("minishell: cd: too many arguments\n");
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	utils_2.c: 2.	*/
/*	Updating the PWD entry on env after successful CD usage.
	Also don't forget about replacing OLDPWD!				*/

static char	**update_env_pwd(char **env, char *old_pwd, int i, int j)
{
	char	buffer[1024];
	char	pwd[1024];
	char	**new_env;

	getcwd(buffer, sizeof(buffer));
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	while (buffer[++i])
		pwd[++j] = buffer[i];
	pwd[j + 1] = 0;
	new_env = update_env(env, "PWD", 1);
	new_env = update_env(new_env, "OLDPWD", 1);
	new_env = update_env(new_env, pwd, 0);
	new_env = update_env(new_env, old_pwd, 0);
	return (new_env);
}

/*	utils_2.c: 3.	*/

static int	find_env_pwd(char **env, int i, int j)
{
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
		{
			if (env[i][3] == '=' && env[i][4] != '=')
			{
				j = i;
				break ;
			}
		}
		i++;
	}
	return (j);
}

/*	utils_2.c: 4.	*/
/*	Taking the current work directory and adding "OLD" as a prefix
	since chdir is about to change directories.				*/

static char	*writing_old_pwd(char **env, int i, int j)
{
	char	*old_pwd;
	int		x;

	j = find_env_pwd(env, 0, 0);
	while (env[j][i])
		i++;
	old_pwd = malloc(sizeof(char) * (i + 1 + 3));
	if (!old_pwd)
		return (NULL);
	old_pwd[0] = 'O';
	old_pwd[1] = 'L';
	old_pwd[2] = 'D';
	i = 3;
	x = 0;
	while (env[j][x])
	{
		old_pwd[i] = env[j][x];
		i++;
		x++;
	}
	old_pwd[i] = 0;
	return (old_pwd);
}

/*	utils_2.c: 5.	*/
/*	Checking if there's a viable directory path, switching if possible.

	The regular "cd"-command (without a directory/path) is not supported.	*/

char	**change_directory(char *str, char **env, int i, int j)
{
	char	cd[1024];
	char	*old_pwd;

	old_pwd = writing_old_pwd(env, 0, 0);
	if (!old_pwd)
		return (env);
	i = skip_spaces(str, 0) + 2;
	i = skip_spaces(str, i);
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != 9)
	{
		cd[j] = str[i];
		j++;
		i++;
	}
	cd[j] = 0;
	if (check_cd_errors(str, cd, i))
		return (env);
	else if (chdir(cd))
		printf("minishell: cd: %s: Not a directory\n", cd);
	else
		env = update_env_pwd(env, old_pwd, -1, 3);
	return (env);
}
