/*
** run_action.c for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 19:21:57 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 20:17:38 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "client.h"
#include "salon.h"
#include "run_action.h"

int		move_to(t_client *c, char *salon)
{
  t_link	*ltmp;
  t_salon	*stmp;
  
  if (c->salon == NULL || c->salon->first == NULL)
    {
      my_log(__func__, "client's salons list is empty", 2);
      return (RUNTIME_ERROR);
    }
  ltmp = c->salon->first;
  while (ltmp)
    {
      stmp = (t_salon*)ltmp->content;
      if (!my_strcmp(stmp->name, salon))
	c->actual = ltmp->index;
      ltmp = ltmp->next;
    }
  return (0);
}

int		private_message(t_chain *clients, char *dst_pseudo, char *buffer)
{
  t_link	*ltmp;
  t_client	*c;

  if (clients->first == NULL)
    {
      my_log(__func__, "there is no clients in server's list", 2);
      return (-1);
    }
  ltmp = clients->first;
  while (ltmp)
    {
      c = (t_client*)ltmp->content;
      if (!my_strcmp(c->pseudo, dst_pseudo))
	send(c->sock, buffer, my_strlen(buffer), 0);
      ltmp = ltmp->next;
    }
  return (0);
}
