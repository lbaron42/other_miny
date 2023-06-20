/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_1.c	                	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export_unset_1.c: 1.	*/

char	*add_new_str(char *ref, int i, int j)
{
	char	*str;

	while (ref[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (ref[j])
	{
		str[i] = ref[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

/*	export_unset_1.c: 2.	*/

char	*add_env_str(char **env, int i, int j)
{
	char	*str;
	int		x;
	int		y;

	while (env[i][j])
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	y = j;
	x = 0;
	j = 0;
	while (x < y)
	{
		str[x] = env[i][j];
		x++;
		j++;
	}
	str[x] = 0;
	return (str);
}

/*	export_unset_1.c: 3.	*/

static char	**add_env(char **env, char *ref, int i, int j)
{
	char	**new;

	while (env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	j = i;
	i = 0;
	while (i < j)
	{
		new[i] = add_env_str(env, i, 0);
		if (!new[i])
		{
			ft_free_array(new);
			return (NULL);
		}
		i++;
	}
	new[i] = add_new_str(ref, i, 0);
	new[i + 1] = 0;
	if (!new[i])
		ft_free_array(new);
	return (new);
}

/*	export_unset_1.c: 4.	*/
/*	Checking if there's a flag that needs to be overwritten in case "export"
	uses the same flagname.	Using a buffer to shorten the reference string
	since it only should contain the flagname for rem_env to work.			*/

static char	**check_for_dupes(char **env, char *ref, int mode)
{
	char	**new;
	char	buf[1024];
	int		i;

	if (mode)
		return (env);
	if (check_valid_export_unset(env, ref, 0, 1))
	{
		i = -1;
		while (ref[++i] && ref[i] != '=')
			buf[i] = ref[i];
		buf[i + 1] = 0;
		new = rem_env(env, buf);
		ft_free_array(env);
		return (new);
	}
	else
		return (env);
}

/*	export_unset_1.c: 5.	*/
/*	Altering the contents of env via the export and unset commands.
	The mode determines if an entry will be added or removed.

	mode 0 = add (export)
	mode 1 = remove (unset)							

	It is highly advised to shut down minishell if env gets corrupted!
	Make sure to quit if "unset" (env_rem) has no valid correspondent!
	Overwrite a pre-existing flag if it gets redefined!			*/

char	**update_env(char **env, char *ref, int mode)
{
	char	**new;

	env = check_for_dupes(env, ref, mode);
	if (!mode)
	{
		new = add_env(env, ref, 0, 0);
		if (!new)
			return (NULL);
	}
	else
	{
		if (!check_valid_export_unset(env, ref, 0, 0))
			return (env);
		new = rem_env(env, ref);
		if (!new)
			return (NULL);
	}
	ft_free_array(env);
	return (new);
}
