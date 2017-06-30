/*
** client.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 11:49:48 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 20 00:36:43 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "util.h"
#include "client.h"

t_client	*init_client()
{
  t_client	*c;

  if ((c = malloc(sizeof(t_client))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  c->sin = NULL;
  c->sock = 0;
  c->pseudo = NULL;
  return (c);
}

int		accept_client(t_chain **clients, int sock)
{
  int           addr_len;
  int           n_sock;
  t_client	*c;
  t_sockaddr_in csin = {0};
  char          buffer[80];

  if (( c = init_client()) == NULL)
    return (SOCKET_ERROR);
  my_log(__func__, "new client want to connect", 3);
  addr_len = sizeof(csin);
  if ((n_sock = accept(sock, (t_sockaddr*)&csin, (socklen_t*)&addr_len)) == SOCKET_ERROR)
    {
      my_log(__func__, "accept connection failed", 1);
      return (SOCKET_ERROR);
    }
  sprintf(buffer, "accept new client connection at %s on port %d succeeded.", inet_ntoa(csin.sin_addr), htons(\
													      csin.sin_port));
  my_log(__func__, buffer, 3);
  c->sin = &csin;
  c->sock = n_sock;
  if (add_link(clients, c))
    {
      my_log(__func__, "add client to clients' list failed", 1);
      return (SOCKET_ERROR);
    }
  return (0);
}

int		register_client(t_chain **clients, fd_set *readfs, int max_sd)
{
  t_link	*ltmp;
  t_client	*c;
  int		n;
  char		buffer[80];
  
  my_log(__func__, "new client accepted on server", 3);
  ltmp = (t_link*)(*clients)->last;
  c = (t_client*)ltmp->content;
  max_sd = c->sock > max_sd ? c->sock : max_sd;
  FD_SET(c->sock, readfs);
  if ((n = recv(c->sock, buffer, 79, 0)) > 0)
    {
      my_putstr("\n");
      buffer[n] = 0;
      my_putstr(buffer);
      c->pseudo = my_strdup(buffer);
      clear_buff(buffer);
    }
  else
    {
      my_log(__func__, "no pseudo with the connection request", 2);
      sprintf(buffer, "you should give a pseudo: -p 'yourpseudo'");
      send(c->sock, buffer, 79, 0);
      remove_link(clients, ltmp);
      return (SOCKET_ERROR);
    }
  return (max_sd);
}

void		free_clients(t_chain **clients)
{
  t_link	*ltmp;
  t_client	*ctmp;

  ltmp = (*clients)->first;
  while (ltmp)
    {
      ctmp = (t_client*)ltmp->content;
      if (ctmp != NULL)
	{
	  if (ctmp->pseudo != NULL)
	    free(ctmp->pseudo);
	  free(ctmp);
	}
      ltmp = ltmp->next;
    }
}
