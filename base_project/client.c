/*
** client.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 11:49:48 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:34:23 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "server.h"
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
  my_strcpy(c->room, "mainRoom");
  c->sock = 0;
  c->pseudo = NULL;
  return (c);
}

t_client	*accept_client(int sock)
{
  int           addr_len;
  int           n_sock;
  t_client	*c;
  t_sockaddr_in csin = {0};
  char          buffer[BUFF_SIZE];

  if (( c = init_client()) == NULL)
    return (NULL);
  my_log(__func__, "new client want to connect", 3);
  addr_len = sizeof(csin);
  if ((n_sock = accept(sock, (t_sockaddr*)&csin, (socklen_t*)&addr_len)) == SOCKET_ERROR)
    {
      my_log(__func__, "accept connection failed", 1);
      return (NULL);
    }
  sprintf(buffer, "accept new client connection at %s on port ntohd: %d, simple: %d succeeded.",\
	  inet_ntoa(csin.sin_addr), ntohs(csin.sin_port), csin.sin_port);
  my_log(__func__, buffer, 3);
  c->sock = n_sock;
  //clear_buff(buffer);
  return c;
}

int             check_client(t_chain **clients, t_client *c, char *buffer)
{
  int           n;
  t_link        *ltmp;
  char          *usrn;
  ltmp = (t_link*)(*clients)->first;
  if ((n = recv(c->sock, buffer, BUFF_SIZE, 0)) > -1)
  {
      while(ltmp)
      {
        usrn = buffer;
        if ((my_strcmp(usrn, ((t_client *)ltmp->content)->pseudo)) == 0)
        {
                my_log(__func__, "this pseudo is already taken", 2);
                sprintf(buffer, "this pseudo is already taken");
                send(c->sock, buffer, BUFF_SIZE, 0);
                close(c->sock);
                clear_buff(buffer);
                return (REGISTER_ERROR);
        }
        ltmp = ltmp->next;
      }
      my_putstr("\n");
      buffer[n] = 0;
      my_putstr(buffer);
      c->pseudo = my_strdup(buffer);
      message_maker(c, buffer, CONNECTED);
      return (REGISTERED);
  }
  else
  {
      my_log(__func__, "no pseudo with the connection request", 2);
      sprintf(buffer, "you should give a pseudo: -p 'yourpseudo'");
      send(c->sock, buffer, BUFF_SIZE, 0);
      remove_link(clients, ltmp);
      clear_buff(buffer);
      return (REGISTER_ERROR);
  }
  return (0);
}


int		register_client(t_chain **clients, fd_set *readfs, int max_sd, t_client *client)
{
  t_client	*c;
  char		buffer[BUFF_SIZE];
  
  my_log(__func__, "new client accepted on server", 3);
  c = client;
  max_sd = c->sock > max_sd ? c->sock : max_sd;
  FD_SET(c->sock, readfs);
  if ((check_client(clients, client, buffer)) > 0)
    {
      if (add_link(clients, c))
	{
	  my_log(__func__, "add client to clients list failed", 1);
	  return (-1);
	}
	send_msg_to_all((*clients), buffer, c->room, c);
    }
  else
    {
      my_log(__func__, "check client failed", 3);
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
