/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:26:43 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/27 22:28:40 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* COLOR */
# define RED "\033[0;31m"
# define WHITE "\x1B[37m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

/* COMMAND TYPES */
# define CMD 1
# define ARG 2
# define PIPE 3
# define FILE 4
# define REDIN 5
# define REDOUT 6
# define APPEND 7
# define HEREDOC 8
//# define SPACE		10

/* MSG ERROR */
# define ER_MALLOC "malloc error.\n"
# define ER_SHELL "shell error.\n"
# define ER_PARSING "parsing error.\n"

/* CODE ERROR */
# define EXT_MALLOC 1
# define EXT_SHELL 2
# define EXT_PARSING 3
# define EXT_COMMAND_NOT_FOUND 127

/* GNL */
# define BUFFER_SIZE 10

extern pid_t		g_sigpid;

typedef struct s_cmd
{
	bool			append;
	char			**infile;
	char			**outfile;
	char			**cmd_list;
	char			**limiters;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**env;
	t_token			*token;
	t_cmd			*cmd;
	int				ecode;
	int				last_pid;
}					t_shell;

/* MAIN */
int					minishell(char **env);

/* PARSING */
int					parsing(t_shell *shell, char *input);
void				add_cmd(t_cmd **head, t_cmd *ncmd);
t_token				*tokenize(char **str);
t_cmd				*token_to_command(t_token *token);
t_token				*determine_type(t_cmd **head, t_cmd **cmd, t_token *token);

/* FREE */
void				free_all(t_shell *shell, char *emsg, int ecode);
void				free_token(t_token *head);
void				free_cmd(t_cmd *head);
void				free_tab(char **str);

/* SIGNALS */
void				signal_handler(int signum);
void				set_sigact(void);
void				signal_child(void);

/* BULTIN */
void				echo(char *options, t_shell *shell);
void				ft_env(t_shell *shell);
void				export(t_shell *shell, char *env);
int					cd(t_shell *shell, char *path);

/* ENV	*/
char				*ft_getenv(char *env_variable, t_shell *shell);
int					ft_getenv_pos(char *env_variable, t_shell *shell);

/*UTILS*/
char				**ft_freetab(char **tab);
char				**append_str(char **tab, char *str);

/* EXECUTION */
void				simple_execution(t_cmd *cmd, t_shell *shell, int pipin,
						int pipout);
void				execute_cmd(t_shell *shell);
void				manage_infile(char **files, int *pipefd, char *cmd);
int					manage_outfile(char **files, int append);
char				*find_path(char *program, t_shell *shell);

/* HEREDOCS */
int				do_all_heredocs(char **heredocs);

/* PRINT ERRORS */
void				print_no_file_error(char *cmd, char *file, int issue);

/* GNL */
char				*get_next_line(int fd);

#endif