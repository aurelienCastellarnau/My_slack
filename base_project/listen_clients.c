/*
** listen_clients.c for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Apr 27 22:26:37 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:18:04 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "util.h"
#include "init_run_params.h"
#include "run_parse.h"
#include "listen_clients.h"

int	listen_clients(t_chain **clients,
			t_chain **salons,
			t_link *ltmp,
			t_client *c)
{
  int	ret;
  char	buffer[BUFF_SIZE];

  my_log(__func__, "Something happend on client sock", 3);
  if ((ret = recv(c->sock, buffer, BUFF_SIZE, 0)) <= 0)
    {
      if (disconnect_one(clients, c, ltmp, buffer) == -1)
	  return (1);
    }
  else
    {
      buffer[ret] = 0;
      if ((ret = run_parse(c, buffer, salons, clients)) == CMD)
	my_log(__func__, "command valid", 3);
      else if (ret == PARSE_ERROR)
	my_log(__func__, "command invalid", 2);
      else
	{
	  message_maker(c, buffer, CLIENT);
	  send_msg_to_all(*clients, buffer, c->room, c);
	}
    }
  return (ret);
}

int		disconnect_one(t_chain **clients, t_client *c, t_link *ltmp, char *buffer)
{
  message_maker(c, buffer, DISCONNECTED);
  send_msg_to_all(*clients, buffer, c->room, c);
  close(c->sock);
  sprintf(buffer, "%s disconnected ", c->pseudo);
  my_log(__func__, buffer, 3);
  if (remove_link(clients, ltmp) == -1)
    {
      (*clients) = create_chain(free_clients);
      my_log(__func__, "last link kill", 4);
      return (-1);
    }
  return (0);
}
