/*
** server.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 16 15:46:32 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 22:02:58 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "init_run_params.h"
#include "server.h"
#include "client.h"
#include "util.h"
#include "component.h"
#include "server_action.h"
#include "client.h"
#include "server.h"
#include "salon.h"

int		init_sock(int *sock, t_chain **clients, t_chain **salons)
{
  t_sockaddr_in	*sin;

  if ((*clients = create_chain(NULL)) == NULL)
    return (SOCKET_ERROR);
  if ((*salons = create_chain(NULL)) == NULL)
    return (SOCKET_ERROR);
  if ((*sock = get_socket()) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  if ((sin = get_addrin()) == NULL)
    {
      my_log(__func__, "get addrin", 1);
      return (SOCKET_ERROR);
    }
  if (bind_to((*sock), sin) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  if (listen_to((*sock), MAX_CLIENT) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  return (*sock);
}

int		init_server()
{
  t_chain	*clients;
  t_chain	*salons;
  int		max_sdr;
  int		sock;
  fd_set	read_fds;
  t_client	*client;

  if ((max_sdr = init_sock(&sock, &clients, &salons)) == SOCKET_ERROR)
    return (1);
  if (init_salon(&salons) == NULL)
    return (1);
  while (1)
    {
      max_sdr = set_fds(&read_fds, sock, clients);
      if (select(max_sdr + 1, &read_fds, NULL, NULL, NULL) < 0)
	{
	  my_log(__func__, "select failed", 4);
	  continue;
	}
      if (FD_ISSET(STDIN_FILENO, &read_fds))
	  if (server_talking(&clients) == 1)
	    return (1);
      if (FD_ISSET(sock, &read_fds))
	{
	  my_log(__func__, "client acceptation", 4);
	  client = accept_client(sock);
	  max_sdr = register_client(&clients, &read_fds, max_sdr, client);
	}
      else
	{
	  my_log(__func__, "manage transmission: ", 4);
	  manage_transmission(&clients, &salons, &read_fds);
	}
    }
   return (0);
}


int	server_talking(t_chain **clients)
{
  char	*str;
  
  my_log(__func__, "keyboard entry", 4);
  if ((str = readline()) != NULL)
    {
      message_maker(NULL, str, BROADCAST);
      send_msg_to_all(*clients, str, 0, NULL);
      free(str);
      return (0);
    }
  else
    {
      my_log(__func__, "readline problem", 1);
      return (1);
    }
}
