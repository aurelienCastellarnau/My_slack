/*
** server.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 16 15:46:32 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 19 16:46:17 2017 CASTELLARNAU Aurelien
*/

#include <string.h>
#include "util.h"
#include "libmy.h"
#include "server.h"

int		get_connection(t_sockaddr_in *sin)
{
  int		sock;
  char		str[80];

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
      my_log(__func__, "socket init", 1);
      return (SOCKET_ERROR);
    }
  else
    my_log(__func__, "socket init ok", 3);
  if (connect(sock, (t_sockaddr*)sin, sizeof(t_sockaddr)) == SOCKET_ERROR)
    {
      sprintf(str, "Client connection at %s on port %d failed. Server offline", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
      my_log(__func__, str, 1);
      return (SOCKET_ERROR);
    }
  else
    sprintf(str, "Client connection at %s on port %d succeeded.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
  my_log(__func__, str, 3);
  return (sock);
}

int		write_to_server(int sock, const char *buffer)
{
  if (send(sock, buffer, my_strlen(buffer), 0) == SOCKET_ERROR)
    {
      my_log(__func__, "send operation failed", 1);
      return (SOCKET_ERROR);
    }
  return (0);
}

int		init_server()
{
  int		sock;
  char		buffer[80];
  t_sockaddr_in sin;
  fd_set	readfs;
  int		n;
  
  if ((sin.sin_addr.s_addr = inet_addr("127.0.0.1")) == (in_addr_t)(-1))
    {
      my_log(__func__, "innet addr", 1);
      return (SOCKET_ERROR);
    }
  else
    my_log(__func__, "inet_addr ok", 3);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(3000);
  if ((sock = get_connection(&sin)) == SOCKET_ERROR)
    return (SOCKET_ERROR);
  write_to_server(sock, "Hi im new on the saloon!");
  while (1)
    {
      FD_ZERO(&readfs);
      FD_SET(STDIN_FILENO, &readfs);
      FD_SET(sock, &readfs);
      if (select(sock + 1, &readfs, NULL, NULL, NULL) == SOCKET_ERROR)
	{
	  my_log(__func__, "select error", 1);
	  return (SOCKET_ERROR);
	}
      if (FD_ISSET(STDIN_FILENO, &readfs))
	{
	  my_log(__func__, "entry detected on keyboard", 3);
	  fgets(buffer, 79, stdin);
   	  {
	    my_log(__func__, "into fgets", 3);
	    char *p = NULL;
	    p = my_strstr(buffer, "\n");
	    if (p != NULL)
	      {
		*p = 0;
	      }
	    else
	      buffer[79] = 0;
	  }
	  write_to_server(sock, buffer);
	}
      if (FD_ISSET(sock, &readfs))
	{
	  if ((n = recv(sock, buffer, 79, 0)) == SOCKET_ERROR)
	    my_log(__func__, "recv from sock failed", 2);
	  else if (n == 0)
	    {
	      my_log(__func__, "Server disconnected", 2);
	      break;
	    }
	  else
	    {
	      my_putstr_color("cyan", buffer);
	      clear_buff(buffer);
	      continue;
	    }
	}
    }
  close(sock);
  my_log(__func__, "socket successfully closed", 3);
  return (0);
}
