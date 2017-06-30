/*
** util_client.c for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 26 23:03:09 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 20:55:20 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "util.h"
#include "util_client.h"

int	check_pseudo(t_link *ltmp, t_client *c, char *buffer, int n)
{
  char	*usrn;

  my_log(__func__, "begin", 4);
  while(ltmp)
    {
      usrn = buffer;
      my_log(__func__, "in while", 4);
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
  my_log(__func__, "buffer content", 4);
  my_putstr(buffer);
  c->pseudo = my_strdup(buffer);
  message_maker(c, buffer, CONNECTED);
  return (REGISTERED);
}
