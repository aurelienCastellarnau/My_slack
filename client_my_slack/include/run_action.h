/*
** run_action.h for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 23 17:39:44 2017 CASTELLARNAU Aurelien
** Last update Sun Apr 23 17:41:35 2017 CASTELLARNAU Aurelien
*/

#ifndef  _RUN_ACTION_H_
# define _RUN_ACTION_H_

int	move_to(t_client *c, char *salon);
int	private_message(t_chain *clients, char *dst_pseudo, char *buffer);

#endif  /* !_RUN_ACTION_H_ */
