/*
** init_run_params.h for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 26 13:51:35 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 16:41:25 2017 CASTELLARNAU Aurelien
*/

#ifndef  _INIT_RUN_PARAMS_H_
# define _INIT_RUN_PARAMS_H_

typedef struct	s_run_params
{
  char		*buffer;
  t_client      *current;
  t_chain       **salons;
  t_chain       **clients;
  t_option      *option;
}		t_run_params;

t_run_params	*init_run_params();

#endif  /* !_INIT_RUN_PARAMS_H_ */ 
