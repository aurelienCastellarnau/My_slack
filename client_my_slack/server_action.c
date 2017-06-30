/*
** server_action.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:20:43 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:53:03 2017 MASERA Mathieu
*/

#include <sys/types.h>
#include "libmy.h"
#include "struct.h"
#include "util.h"
#include "client.h"
#include "server.h"
#include "server_action.h"
#include "const.h"

int	connect_to(int sock, t_sockaddr_in *sin, char *pseudo)
{
  char	buffer[40];

  if (connect(sock, (t_sockaddr*)sin, sizeof(t_sockaddr_in)) == SOCKET_ERROR)
    {
      sprintf(buffer, "Server connect to %s on port %d failed.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
      my_log(__func__, buffer, 3);
      return (SOCKET_ERROR);
    }
  sprintf(buffer, "Server connect to %s on port %d succeeded.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
  if (send(sock, pseudo, my_strlen(pseudo) + 1, 0) == SOCKET_ERROR)
    {
      my_log(__func__, "pseudo not send", 1);
      return (SOCKET_ERROR);
    }
  my_log(__func__, "send pseudo ok", 3);
  my_log(__func__, buffer, 3);
  return (0);  
}

/*
** Set all file descriptor to listen
** return the bigger socket.
*/
int		set_fds(fd_set *readfs, t_client *client)
{
  FD_ZERO(readfs);
  FD_SET(STDIN_FILENO, readfs);
  if (client != NULL && client->sock > 0)
    FD_SET(client->sock, readfs);
  else
    {
      my_log(__func__, "client or client socker", 1);
      return (SOCKET_ERROR);
    }
  return (0);
}

int		send_to_all(t_client *c)
{
  char		*input;

  if ((input = readline()) == NULL)
    {
      my_log(__func__, "empty send", 2);
      return (0);
    }
  else if (c != NULL && c->sock > 0)
    {
      if (send(c->sock, input, my_strlen(input) + 1, 0) == SOCKET_ERROR)
	{
	  my_log(__func__, "message not send", 1);
	  return (SOCKET_ERROR);
	}
      my_log(__func__, "send ok", 3);
    }
  return (0);
}

int		receive_on(t_client *c)
{
  int		n;
  char		buffer[BUFF_SIZE];

  if ((n = recv(c->sock, buffer, BUFF_SIZE - 1, 0)) > 0)
    {
      check_message(c, buffer);
      my_putstr("\n");
      buffer[n] = 0;
      my_putstr(buffer);
      my_putstr("\n");
      clear_buff(buffer);
    }
  else
    {
      my_log(__func__, "server deconnection", 1);
      return (SOCKET_ERROR);
    }
  return (0);
}
