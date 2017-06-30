/*
** run_parse.h for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/client_my_slack
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 14:31:22 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 01:24:46 2017 MASERA Mathieu
*/

#ifndef  _RUN_PARSE_H_
#define  _RUN_PARSE_H_

t_chain		*get_run_opts();
int		format_run_option(char *buffer);
int		exec_run(t_option* opt, t_chain **salons, t_chain **clients);
int		run_parse(char *buffer, t_chain **salons, t_chain **clients);

#endif	 /* !_RUN_PARSE_H_ */
