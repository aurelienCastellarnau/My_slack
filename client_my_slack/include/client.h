/*
** client.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 11:46:24 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:18:20 2017 MASERA Mathieu
*/

#ifndef  _CLIENT_H_
# define _CLIENT_H_

typedef struct	s_client
{
  char		*pseudo;
  t_sockaddr_in	*sin;
  int		sock;
  char		room[20];
}		t_client;

t_client	*init_client();
int		set_pseudo(t_chain *parameters, t_client **c);
void		delete_client(t_client **c);

#endif /* !_CLIENT_H_ */
