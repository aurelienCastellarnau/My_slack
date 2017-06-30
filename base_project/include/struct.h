/*
** struct.h for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Apr 27 20:48:43 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:18:15 2017 CASTELLARNAU Aurelien
*/

#ifndef  _STRUCT_H_
# define _STRUCT_H_

typedef struct	s_client
{
  char		room[20];
  char		*pseudo;
  int		sock;
  t_chain	*salon;
}		t_client;


#endif  /* !_STRUCT_H_ */
