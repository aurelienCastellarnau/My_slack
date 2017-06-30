/*
** server.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
a** Started on  Sun Apr 16 15:46:32 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:26:19 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "util.h"
#include "component.h"
#include "client.h"
#include "server.h"
#include "server_action.h"
#include "const.h"

int	get_connection(char *pseudo)
{
  int		tmp_sock;
  t_sockaddr_in	*addr_in;
 
  if ((addr_in = get_addrin()) == NULL)
    {
      my_log(__func__, "get addrin", 1);
      return (SOCKET_ERROR);
    }
  if ((tmp_sock = get_socket()) == SOCKET_ERROR)
    {
      my_log(__func__, "get socket", 1);
      return (SOCKET_ERROR);
    }
  if (connect_to(tmp_sock, addr_in, pseudo) == SOCKET_ERROR)
    {
      my_log(__func__, "connect to", 1);
      return (SOCKET_ERROR);
    }
  free(addr_in);
  return (tmp_sock);
}

int	workflow(t_client *client)
{
  fd_set	readfs;
  int		bool;

  while (1)
    {
      bool = 0;
      if (set_fds(&readfs, client) == SOCKET_ERROR)
	return (SOCKET_ERROR);
      if ((bool = select(client->sock + 1, &readfs, NULL, NULL, NULL)) < 0)
	  my_log(__func__, "A client leaved the server", 2);
      if (bool >= 0 && FD_ISSET(STDIN_FILENO, &readfs))
	{
	  if (send_to_all(client) == SOCKET_ERROR)
	    return (SOCKET_ERROR);
	}
      else if (bool >= 0 && FD_ISSET(client->sock, &readfs))
	  if (receive_on(client) == SOCKET_ERROR)
	    return (SOCKET_ERROR);
    }
}

int		init_server(t_client **c)
{
  t_client	*client;

  client = (*c);
  if ((client->sock = get_connection(client->pseudo)) == SOCKET_ERROR)
    {
      my_log(__func__, "socket init failed", 1);
      return (1);
    }
  else
    my_log(__func__, "socket init ok", 4);
  if (workflow(client) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  close(client->sock);
  my_log(__func__, "socket successfully closed", 3);
  return (0);
}
