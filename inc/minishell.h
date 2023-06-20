/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:41:07 by agrun             #+#    #+#             */
/*   Updated: 2023/05/17 12:41:09 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>

# define MAX_TOKEN_LENGTH 100
# define BUFFER_SIZE 1024

typedef struct s_token{
	int token_code;
	int index;
	char *token;
	char *value;
	struct s_token *next;
}t_token;

//main.c

void	sigint_handler(int sig);
char	**check_commands(char *str, char **env);

//brackets.c

void	check_for_brackets(char *str, char *new, int i, int j);

//utils_1.c

int		ft_strncmp(char *ref, char *input, int i, int j);
int		empty_check(char *str, int i);
int		ft_exit(char *str, char **env);
int		ft_error(int error, char *prompt, char **env);

//utils_2.c

char	**change_directory(char *str, char **env, int i, int j);

//utils_3.c

int		ft_return(int r, int mode);
void	rewrite_prompt(char *str, char *buffer, int i, int j);
int		ft_find_word(char *str, char *ref, int i, int j);
int		ft_find_bracketed_flag(char *str);
int		check_echo_prefix(char *str);

//utils_4.c

int		check_alpha_num(char *echo, int *i);
void	adjust_flag_string(char *str, char *buf, int i);
int		check_qm_prompt(char *str, int hide_error);
int		skip_flags(char *str, int i);
int		skip_spaces(char *str, int i);

//shell_commands.c

char	**check_shell_commands(char *str, char **envp, int hide_error);
int		check_extended_shell_commands(char *ref);
void	define_format(char *str, char **env, int i, int j);

//flag_commands_1.c

void	skip_quotes_and_brackets(char *str, int *flag, int *i, int n);
int		check_flag_commands(char *str, char **env, int hide_e);

//flag_commands_2.c

int		display_found_flag(char *buf, char **env, int flag, int hide_e);

//export_unset_1.c

char	*add_new_str(char *ref, int i, int j);
char	*add_env_str(char **env, int i, int j);
char	**update_env(char **env, char *ref, int mode);

//export_unset_2.c

int		ft_array_len(char **str);
char	**rem_env(char **env, char *ref);
char	**copy_env(char **envp);
int		check_valid_export_unset(char **env, char *ref, int i, int mode);

//export_unset_3.c

void	print_env(char **env, int n);
char	**check_export_unset(char *str, char **env);

//echo_1.c

int		check_next_quotation_mark(char *echo, int i, int mode);
int		print_echo(char *str, int i, int j, char **envp);

//echo_2.c

void	handle_echo_rules(char *echo, int *i, int *quote_flag, char **envp);

//echo_3.c

int		check_echo_errors(char *echo, int *x);

//echo_4.c

int		handle_qm(int *i);
int		check_available_commands(char *buf);
void	display_echo_errors(char *echo, int i, int flag);

//echo_5.c

int		ft_format_error(char *str, int code, int i, int j);
int		display_known_flags(char *str, int *i, int special, char **env);

//free.c

int		ft_free_array(char **array);
int		ft_free(char **str);

//run_built_in_1.c

int		check_next_operator(char **str);
void	run_pwd_env(char **tmp, char **envp, int mode);
char	**run_cd_export_unset_echo(char **tmp, char **envp, int mode);
char	**run_built_in(char **tmp, char **envp);

//run_built_in_2.c

void	rewrite_tmp_3(char **tmp, char **envp);
void	rewrite_tmp_2(char **tmp, char *buffer, char **envp, int mode);
void	rewrite_tmp(char **tmp, char *buffer, char **envp, int mode);
void	rewrite_buffer(char **tmp, char *buffer, int i, int x);

//access_utils_1.c

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*join_strings(const char *str1, const char *str2, const char *str3);

//access_utils_2.c

char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_word_count(const char *str, char c);
int		ft_size_word(const char *s, char c, int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//access_utils_3.c

char	**ft_free_str(char **strs, int j);
char	**ft_split(char const *s, char c);
int		ft_og_strncmp(const char *s1, const char *s2, size_t n);

//access.c

char	**find_path(char **envp);
char	*valid_cmd(char **path, char *cmd);

//lexer

void parser(char **envp, t_token *head);
t_token	*create_token_list(char *input, t_token *head);


#endif
