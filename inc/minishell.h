/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:46:41 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/06 19:47:56 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "heredoc.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

/*		GLOBAL SYMBOLS		*/
typedef enum s_symbol
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_symbol;

/*		TOKEN STRUCT		*/
typedef struct s_token
{
	char			*str;
	t_symbol		token;
	int				i;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*		ONE CMD STRUCT		*/
typedef struct s_parser_cmd
{
	t_token			*lexer_list;
	t_token			*redirections;
	int				num_redirections;
	struct s_global	*tools;
}	t_parser_cmd;

/*		GLOBAL STRUCT		*/
typedef struct s_global
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_token					*lexer_list;
	t_heredoc	 			heredoc_struct;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_global;

/*		SIMPLE CMD STRUCT		*/
typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_global *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_token					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

/*		INIT FUNCTIONS		*/
int				run_minishell(t_global *global);
int				init_global_struct(t_global *global);

/*		LEXER FUNCTIONS		*/
int				lexer(t_global *global);
t_token			*ft_lexernew(char *str, int token);
void			ft_lexeradd_back(t_token **lst, t_token *new);
void			ft_lexerdelone(t_token **lst, int i);
void			ft_lexerclear(t_token **lst);
int				token_reader(t_global *tools);
int				add_node(char *str, t_symbol token, t_token **lexer_list);
t_symbol		check_token(int c);
int				handle_token(char *str, int i, t_token **lexer_list);

/*		PARSER FUNCTIONS		*/
t_parser_cmd	init_parser(t_token *lexer_list, t_global *global);
int				parse_envp(t_global *global);
void			print_parser(t_simple_cmds simple_cmds);
int				find_pwd(t_global *global);
int				parser(t_global *global);
void			count_pipes(t_token *lexer_list, t_global *global);
int				count_args(t_token *lexer_list);
t_token			*find_next_cmd(t_token *lexer_lst);
t_parser_cmd	init_parser_tools(t_token *lexer_list, t_global *global);
//functions for one cmd
t_simple_cmds	*ft_simple_cmdsnew(char **str,
					int num_redirections, t_token *redirections);
void			ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void			ft_simple_cmds_rm_first(t_simple_cmds **lst);
void			ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds	*ft_simple_cmdsfirst(t_simple_cmds *map);
int				count_quotes(char *line);
int				implement_tools(t_global *tools);
char			**ft_arrdup(char **arr);

/*		EXPANDER FUNCTIONS		*/
char			**expander(t_global *global, char **str);
char			*expander_str(t_global *global, char *str);
size_t			dollar_sign(char *str);
char			*char_to_str(char c);
int				after_dol_lenght(char *str, int j);
void			free_things(char *tmp2, t_global *tools, int i);
int				question_mark(char **tmp, t_heredoc heredoc_struct);

/*		EXECUTOR FUNCTIONS		*/
int			prepare_executor(t_global *global);
int				check_redirections(t_simple_cmds *cmd);
int				executor(t_global *tools);
t_simple_cmds	*call_expander(t_global *tools, t_simple_cmds *cmd);
int				pipe_wait(t_global *global);
int				find_cmd(t_simple_cmds *cmd, t_global *tools);
void			handle_cmd(t_simple_cmds *cmd, t_global *tools);
void			dup_cmd(t_simple_cmds *cmd, t_global *tools,
					int end[2], int fd_in);
void			single_cmd(t_simple_cmds *cmd, t_global *tools);
int				send_heredoc(t_global *tools, t_simple_cmds *cmd);

/*		MESS FUNCTIONS		*/
int				find_pwd(t_global *tools);
int				reset(t_global *tools);
void			init_stri(int i, int j, t_global *tools);
void			free_arr(char **split_arr);

/*		QUOTES FUNCTIONS		*/
char			*delete_quotes_value(char *str);
char			*delete_quotes(char *str, char c);
char			*delete_quotes_export(char *str, char c);
int				handle_quotes(int i, char *str, char del);

/*		SIGNALS FUNCTIONS		*/
void			sigint_handler(int sig);
void			sigquit_handler(int sig);
void			init_signals(t_heredoc heredoc_struct);
int				sig_checker(t_heredoc heredoc_struct);

/*		RESIRECTIONS FUNCTIONS		*/
int				add_new_redirection(t_token *tmp, t_parser_cmd *parser_cmd);
int				handle_heredoc(t_parser_cmd *parser_cmd, t_token *tmp);
void			rm_redirections(t_parser_cmd *parser_cmd);

/*		BUILTIN FUNCTIONS		*/
void			change_path(t_global *global);
int				ft_echo(t_global *global, t_simple_cmds *simple_cmd);
int				ft_cd(t_global *global, t_simple_cmds *simple_cmd);
int				ft_pwd(t_global *global, t_simple_cmds *simple_cmd);
int				ft_export(t_global *global, t_simple_cmds *simple_cmd);
int				ft_unset(t_global *global, t_simple_cmds *simple_cmd);
int				ft_env(t_global *global, t_simple_cmds *simple_cmd);
int				ft_exit(t_global *global, t_simple_cmds *simple_cmd);
int				ft_continue(t_global *global, t_simple_cmds *simple_cmd);
size_t			equal_sign(char *str);
int				check_valid_identifier(char c);
int				(*builtin_arr(char *str))(t_global *global, t_simple_cmds *simple_cmd);

/*		ERRORS FUNCTIONS		*/
void	parser_error(int error, t_global *tools, t_token *lexer_list);
int		parser_double_token_error(t_global *tools, t_token *lexer_list,t_symbol token);
void	lexer_error(int error, t_global *tools);
int		cmd_not_found(char *str);
int		export_error(char *c);
int		ft_error(int error, t_global *tools);

#endif