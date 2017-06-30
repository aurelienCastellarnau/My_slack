/*
** salon.h for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 19:05:58 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:47:32 2017 CASTELLARNAU Aurelien
*/

#ifndef  _SALON_H_
#define _SALON_H_

typedef struct	s_salon
{
  char		name[20];
  t_chain	*clients;
  t_chain	*allowed_clients;
}		t_salon;

t_salon		*new_salon(t_chain **opt_parameters, t_run_params *run_param);
void		free_salons(t_chain **salons);
t_salon		*init_salon(t_chain **salons);
char		*list_salons(t_chain *salons);
void		salon_messenger(t_client *c, char *salon, t_chain **clients, int type);

#endif   /* !_SALON_H_ */
