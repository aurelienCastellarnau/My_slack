/*
** client.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 11:46:24 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 20 00:43:50 2017 CASTELLARNAU Aurelien
*/

#ifndef  _CLIENT_H_
# define _CLIENT_H_

#include "libmy.h"
#include "server.h"

typedef struct	s_client
{
  char		*pseudo;
  t_sockaddr_in	*sin;
  int		sock;
}		t_client;

int		accept_client(t_chain **clients, int sock);
int		register_client(t_chain **clients, fd_set *readfs, int max_sd);
void		free_clients(t_chain **clients);

#endif /* !_CLIENT_H_ */
