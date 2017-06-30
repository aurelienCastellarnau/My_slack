/*
** run_parse.h for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/client_my_slack
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 14:31:22 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 16:18:06 2017 CASTELLARNAU Aurelien
*/

#ifndef  _RUN_PARSE_H_
# define _RUN_PARSE_H_
# define CMD 2

t_chain		*get_run_opts();
int		format_run_option(char *buffer);
int		exec_run(t_run_params *parameters);
int		run_parse(t_client *current, char *buffer, t_chain **salons, t_chain **clients);

#endif	 /* !_RUN_PARSE_H_ */
