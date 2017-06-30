/*
** server_action.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:20:43 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 20 00:30:48 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "util.h"
#include "client.h"
#include "server.h"
#include "server_action.h"

int	bind_to(int sock, t_sockaddr_in *sin)
{
  char	buffer[40];

  if (bind(sock, (t_sockaddr*)sin, sizeof(t_sockaddr_in)) == SOCKET_ERROR)
    {
      sprintf(buffer, "Server bind at %s on port %d failed.", inet_ntoa(sin->sin_addr), htons(sin->sin_port));
      my_log(__func__, buffer, 3);
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

int		broadcast(t_chain *clients)
{
  char		*input;
  t_link	*ltmp;
  t_client	*c;

  if ((input = readline()) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (SOCKET_ERROR);
    }
  ltmp = clients->first;
  while (ltmp)
    {
      c = (t_client*)ltmp->content;
      send(c->sock, input, my_strlen(input) + 1, 0);
      my_log(__func__, "send ok", 3);
      ltmp = ltmp->next;
    }
  free(input);
  input = NULL;
  return (0);
}

int		manage_transmission(t_chain **clients, fd_set *readfs)
{
  t_link	*ltmp;
  t_link	*inner_ltmp;
  int		n;
  t_client	*c;
  char		buffer[80];
  
  ltmp = (*clients)->first;
  while(ltmp)
    {
      c= (t_client*)ltmp->content;
      if (FD_ISSET(c->sock, readfs))
	{
	  my_log(__func__, "Something happend on client sock", 3);
	  if ((n = recv(c->sock, buffer, 79, 0)) == SOCKET_ERROR)
	    my_log(__func__, "receiving client socket content failed", 2);
	  else if (n == 0)
	    {
	      my_log(__func__, "client disconnected", 3);
	      close(c->sock);
	      remove_link(clients, ltmp);
	    }
	  else
	    {
	      my_log(__func__, "message received: ", 3);
	      my_putstr(buffer);
	      inner_ltmp = (*clients)->first;
	      while (inner_ltmp)
		{
		  c = (t_client*)inner_ltmp->content;
		  if (ltmp != inner_ltmp)
		    {
		      send(c->sock, buffer, 19, 0);
		      my_log(__func__, "send ok", 3);
		    }
		  inner_ltmp = inner_ltmp->next;
		}
	      clear_buff(buffer);
	    }
	}
      ltmp = ltmp->next;
    }
  return (0);
}
