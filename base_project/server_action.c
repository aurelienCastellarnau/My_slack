/*
** server_action.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:20:43 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:37:15 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 16:15:02 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "struct.h"
#include "client.h"
#include "server.h"
#include "init_run_params.h"
#include "util.h"
#include "listen_clients.h"
#include "run_parse.h"
#include "run_action.h"
#include "server_action.h"

int	bind_to(int sock, t_sockaddr_in *sin)
{
  char	buffer[BUFF_SIZE];

  if (bind(sock, (t_sockaddr*)sin, sizeof(t_sockaddr_in)) == SOCKET_ERROR)
    {
      sprintf(buffer, "Server bind at %s on port %d failed.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
      my_log(__func__, buffer, 2);
      return (SOCKET_ERROR);
    }
  else
    sprintf(buffer, "Server bind at %s on port %d succeeded.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
  my_log(__func__, buffer, 3);
  return (0);  
}

int	listen_to(int sock, int clients)
{
  if (listen(sock, clients) == SOCKET_ERROR)
    {
      my_log(__func__, "listening failed", 1);
      return (SOCKET_ERROR);
    }
  else
    my_log(__func__, "server listening", 3);
  return (0);
}

/*
** Set all file descriptor to listen
** return the bigger socket.
*/
int		set_fds(fd_set *readfs, int sock, t_chain *clients)
{
  int		max_sd;
  t_link	*ltmp;
  t_client	*c;

  max_sd = sock;
  FD_ZERO(readfs);
  FD_SET(STDIN_FILENO, readfs);
  FD_SET(sock, readfs);
  if (clients == NULL || clients->first == NULL)
    {
      my_log(__func__, "list of clients is empty", 2);
      return (sock);
    }
  ltmp = clients->first;
  while (ltmp)
    {
      c = (t_client*)ltmp->content;
      if (c != NULL && c->sock > 0)
	FD_SET(c->sock, readfs);
      if (c->sock > max_sd)
	max_sd = c->sock;
      ltmp = ltmp->next;
    }
  return (max_sd);
}

/*
** manage bucle on clients
*/
int		manage_transmission(t_chain **clients, t_chain **salons, fd_set *readfs)
{
  t_link	*ltmp;
  t_client	*c;

  my_log(__func__, "manage transmission begin", 4);
  if (chain_is_empty(clients))
    {
      my_log(__func__, "client list is empty", 2);
      return (SOCKET_ERROR);
    }
  ltmp = (*clients)->first;
  while (ltmp)
    {
      c = (t_client*)ltmp->content;
      if (FD_ISSET(c->sock, readfs))
	listen_clients(clients, salons, ltmp, c);
      if (ltmp != NULL)
	ltmp = ltmp->next;
    }
  return (0);
}

