/*
** server.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
a** Started on  Sun Apr 16 15:46:32 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 20 00:44:39 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "util.h"
#include "component.h"
#include "server_action.h"
#include "client.h"
#include "server.h"

int	get_connection()
{
  int		tmp_sock;
  t_sockaddr_in	*addr_in;
 
  if ((addr_in = get_addrin()) == NULL)
    return (SOCKET_ERROR);
  if ((tmp_sock = get_socket()) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  if (bind_to(tmp_sock, addr_in) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  free(addr_in);
  if (listen_to(tmp_sock, 4) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  return (tmp_sock);
}

int	workflow(int sock, t_chain *clients)
{
  int		max_sd;
  fd_set	readfs;
  int		index_client;
  int		max_clients;
  
  max_clients = 4;
  index_client = 0;
  while (1)
    {
      max_sd = set_fds(&readfs, sock, clients);
      if (select(max_sd + 1, &readfs, NULL, NULL, NULL) < 0)
	{
	  my_log(__func__, "A client leaved the server", 2);
	  continue;
	}
      if (FD_ISSET(STDIN_FILENO, &readfs))
	{
	  if (broadcast(clients) == SOCKET_ERROR)
	    return (SOCKET_ERROR);
	}
      else if (FD_ISSET(sock, &readfs))
	{
	  if (index_client + 1 > max_clients)
	    my_log(__func__, "A client want to connect, but no more place on server.", 2);
	  else if (accept_client(&clients, sock) == SOCKET_ERROR)
	    continue;
	  else
	    {
	      if (register_client(&clients, &readfs, max_sd) == SOCKET_ERROR)
		continue;
	      index_client++;
	    }
	}
      else
	manage_transmission(&clients, &readfs);
    }
  
}

int		init_server()
{
  int		sock;
  t_chain	*clients;
  
  sock = 0;
  clients = create_chainf(free_clients);
  if ((sock = get_connection()) == SOCKET_ERROR)
    {
      my_log(__func__, "socket init failed", 1);
      return (1);
    }
  if (workflow(sock, clients) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  close(sock);
  my_log(__func__, "socket successfully closed", 3);
  delete_chainf(&clients);
  my_log(__func__, "clients' list successfully cleared", 3);
  return (0);
}
