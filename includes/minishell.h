/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:15:59 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:19:13 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <stdint.h>
# include <signal.h>
# include <linux/limits.h>
# include <stdint.h>

/* printf, readline */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* to write, read, close, access, pipe, dup, dup2, execve, fork, stat, wait */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>

/* free */
# include <stdlib.h>

/* booleens */
# include <stdbool.h>

/* Error Messages Presets */
# define ERR_MSG_DBQUOTE "QUOTE ERROR : Double quote not closed"
# define ERR_MSG_SPQUOTE "QUOTE ERROR : Simple quote not closed"
# define ERR_MSG_SYNTAX_FILE \
	"INFILE/OUTFILE SYNTAX : Verify near '>' / '<' / '|'"
# define ERR_MSG_SPACE "SYNTAX ERROR : Empty pipe or empty arg"
# define ERR_MSG_EXPORT_NAME "EXPORT NAME ERROR : Var name error"
# define ERR_MSG_BUILTIN_CD \
	"BUILTIN CD ERROR : Too many args"
# define ERR_MSG_BUILTIN_CD_HOME \
		"BUILTIN CD ERROR : Environement var HOME is not set"

extern int	g_signal;

typedef enum e_error
{
	NO_ERROR = 0,
	ERR_DBQUOTE = -1,
	ERR_SPQUOTE = -2,
	ERR_SYNTAX_FILE = -3,
	ERR_OPEN = -4,
	ERR_CLOSE = -5,
	ERR_READ = -6,
	ERR_DUP = -7,
	ERR_PIPE = -8,
	ERR_FORK = -9,
	ERR_SPACE = -10,
	ERR_BUILTIN_CD = -11,
	ERR_BUILTIN_CD_HOME = -12,
	ERR_EMPTY_ARG = -13,
}	t_err;

typedef enum e_syntax
{
	SPQUOTE = 0,
	SPQUOTE_END = 1,
	DBQUOTE = 2,
	DBQUOTE_END = 3,
}	t_stx;

typedef enum e_token
{
	INFILE = O_RDONLY,			// <
	HEREDOC,		// <<
	OUTFILE = O_RDWR | O_CREAT | O_TRUNC, // >
	OUTFILE_APP = O_RDWR | O_CREAT | O_APPEND,	// >>
	CMD = 4,
	REDIRECT_ERR = -1,
}	t_tkn;

typedef struct s_builtincd
{
	int		pwd_l;
	int		oldpwd_l;
	int		home_l;
	char	*newpath;
	char	*oldpath;
	char	buf[PATH_MAX];
}	t_builtincd;

typedef struct s_exprt
{
	int		i;
	bool	written;
	size_t	size;
	char	**newenv;
	char	*argname;
}	t_exprt;

typedef struct s_cpyarg
{
	size_t	tmp;
	size_t	i;
	size_t	size;
	char	*arg_name;
	char	*tmpe;
}	t_cpyarg;

typedef struct s_dbquote
{
	char	*tmp;
	char	*new;
	size_t	i;
	size_t	j;
	size_t	size;
}	t_dbquote;

typedef struct s_quote
{
	char			*quote;
	t_stx			stx_type;
	struct s_quote	*next;
}	t_quote;

typedef struct s_elem
{
	char			*elem;
	t_quote			*quote;
	t_stx			stx_type;
	t_tkn			id;
	struct s_elem	*next;
	struct s_elem	*prev;
}	t_elem;

typedef struct s_tknarg
{
	int		i;
	char	*temp_dup;
	t_tkn	token;
	t_stx	stx;
	t_quote	*quote;
}	t_tknarg;

/* 1 maillon = 1 pipe */
typedef struct s_pipesep
{
	bool				builtin;
	char				*line;
	t_elem				*elems;
	char				**cmd;
	int					infile;
	int					outfile;
	int					fd_pipe[2];
	size_t				len_seps;
	char				*name_heredoc;
	struct s_pipesep	*head;
	struct s_pipesep	*next;
}	t_pipesep;

typedef struct s_envp
{
	char			**env_shell;
	unsigned char	exit_status;
}	t_envp;

typedef struct s_exec
{
	pid_t	pid;
	int		tmp_fd_pipe_in;
	int		time;
	int		tmp_stdin;
	int		tmp_stdout;
}	t_exec;

/* Parsing */
t_err		ft_checkline(char *line);
t_err		ft_error(t_err cd);
t_pipesep	*ft_pipesep(char *line);
void		createcmd(t_pipesep **seps);
int			isredir(char *line, t_tknarg t);

/* Utils */
char		*ft_strndup(const char *str, int n);
void		free_dbtab(char **db_array);
char		**init_envp(char **env);
void		free_lst_seps(t_pipesep **seps);
void		free_lst_elem(t_elem *elem);
bool		ft_iswhitespace(char c);

/* Cat Elems*/
void		elemscat(t_pipesep **seps);
int			ft_checkelems(t_pipesep *seps);

/* Tokenisation */
int			tokenise_file(t_elem **elems, int start, char *line);
int			skipspaces(char *str);
int			tokenise_arg(t_elem **elems, int start, char *line);
t_elem		*tokenise_line(char *line);
void		tokeniser(t_pipesep **seps);
void		tokenise_redir(t_tknarg *t, char *line);

/* Expansion */
void		expander(t_pipesep **seps, char **env, int extsts);
t_err		expand_dbquote(char **content, char **env, int extsts);
int			cancpychar(t_dbquote *d);
size_t		new_size_dbquote(char *elem, char **env, int extsts);
size_t		size_dollar_arg(char *arg, char **env);

/* Liste chainee */
t_pipesep	*ft_lstsep_new(char *content);
t_pipesep	*ft_lstseplast(t_pipesep *lst);
void		ft_lstaddsep_back(t_pipesep **alst, t_pipesep *new);

/* QUotes */
t_quote		*ft_lstquote_new(char *content, t_stx type);
t_quote		*ft_lstquotelast(t_quote *lst);
void		ft_lstquoteadd_back(t_quote **alst, t_quote *new);

t_elem		*ft_lstelem_new(char *content, t_tkn token,
				t_stx type, t_quote *quote);
t_elem		*ft_lstelemlast(t_elem *lst);
void		ft_lstelemadd_back(t_elem **alst, t_elem *new);
size_t		count_elems(t_elem *elems);
size_t		count_seps(t_pipesep *seps);
void		affect_len(t_pipesep *seps);

/*Exec*/
int			execution(t_pipesep *seps, t_envp *envp, t_exec *exec);
int			bool_search_cmd(char *str, int c);
char		*ft_join_cmd(char *s1, char *s2);
void		search_path(t_pipesep *seps, t_envp *envp);
int			child(t_pipesep *seps, t_elem *elem, t_exec *exec, t_envp *envp);
t_err		dup_builtin(t_pipesep *seps, t_envp *envp);
t_err		dup_child(t_pipesep *seps, t_exec *exec, t_envp *envp);
void		close_pipe(t_pipesep *seps, t_exec *exec);
t_err		open_error(t_pipesep *seps, int file, char *name, t_envp *envp);
void		close_and_check_error(int file, char *name);
t_err		execution_builtin(t_pipesep *seps, t_envp *envp, t_exec *exec);

/* Files */
t_err		open_files(t_pipesep *seps, t_envp *envp, t_exec *exec);
int			open_heredoc(t_pipesep *seps, t_envp *envp);
int			init_redir_hd(t_pipesep *seps, t_envp *envp);
t_err		open_files_p(t_pipesep *seps, t_envp *envp);
t_err		open_error_p(t_pipesep *seps, int file, char *name, t_envp *envp);

/* Builtin */
void		if_builtin(t_pipesep *seps);
int			builtin_function(t_pipesep *seps, t_envp *envp, t_exec *exec);
int			builtin_env(t_envp *envp);
int			builtin_pwd(t_envp *envp);
int			builtin_echo(t_pipesep *seps, t_elem *elems, char **cmd);
int			builtin_exit(t_pipesep *seps, t_envp *envp, t_exec *exec);
int			builtin_cd(t_envp *envp, char *arg);
char		*new_oldpwd(char *pwd);
char		*new_pwd(char *pwd);
char		*remove_last_file(char *l);
int			search_env_l(char **env, const char *name);
int			builtin_export(t_envp *envp, char *envar);
void		builtin_export2(t_exprt *e, t_envp *envp, char *envar);
char		*varequal(char *envar);
int			builtin_unset(t_envp **envp, char *envar);
size_t		size_env(char **env);
void		close_builtin(t_exec *exec);

/*Signal*/
void		sig_handler(int signal);
void		init_signal(void);

/* Printing A SUPPRIMER */
//void	doubletabread(char **tab);
void		ft_printsepstoken(t_elem *elems);
void		ft_printseps(t_pipesep *seps);

#endif