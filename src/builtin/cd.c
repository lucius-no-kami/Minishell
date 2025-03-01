/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:49:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/27 10:44:34 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_shell *shell, char *path)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, 4096) == NULL)
	{
		perror(path);
		return (1);
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	export(shell, pwd);
	return (0);
}

int	cd(t_shell *shell, char *path)
{
	int	ret;

	if (path)
	{
		ret = chdir(path);
		if (ret == 0)
			update_pwd(shell, path);
		if (ret != 0)
			perror(path);
		return (ret);
	}
	return (1);
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		printf("Usage: %s path\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cd(argv[1]) != 0)
// 	{
// 		perror("Echec de la commande cd");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }
