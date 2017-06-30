/*
** run_action.h for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 23 17:39:44 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:36:41 2017 CASTELLARNAU Aurelien
*/

#ifndef  _RUN_ACTION_H_
# define _RUN_ACTION_H_

int	move_to(t_client *c, char *salon, t_chain **salons);
int	private_message(t_chain **clients, char *pseudo, char *buffer);
void	send_list(t_client *current, t_chain **salons);

#endif  /* !_RUN_ACTION_H_ */
