/*
** run_action.c for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 19:21:57 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:36:17 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "init_run_params.h"
#include "salon.h"
#include "run_action.h"
#include "util.h"
#include "server.h"

int		move_to(t_client *c, char *salon, t_chain **salons)
{
  t_link	*ltmp;
  t_salon	*stmp;

  if (c->room == NULL)
    {
      my_log(__func__, "client's salons list is empty", 2);
      return (RUNTIME_ERROR);
    }
  ltmp = (*salons)->first;
  while (ltmp)
    {
      stmp = (t_salon*)ltmp->content;
      if (my_strcmp(stmp->name, salon) != 0)
	ltmp = ltmp->next;
      else
	{
	clear_room(c->room);
	my_strcpy(c->room, stmp->name);
	my_log(__func__, "a client moved_to", 3);
	return (0);
      }
    }
  my_log(__func__, "a client failed to move_to", 3); 
  return (0);
}

int		private_message(t_chain **clients, char *pseudo, char *buffer)
{
  t_link	*ltmp;
  t_client	*c;

  my_log(__func__, "send private message", 4);
  if (clients == NULL || (*clients) == NULL || (*clients)->first == NULL)
    {
      my_log(__func__, "there is no clients in server's list", 2);
      return (-1);
    }
  ltmp = (*clients)->first;
  while (ltmp)
    {
      my_log(__func__, "in bucle with: ", 4);
      c = (t_client*)ltmp->content;
      my_putstr(c->pseudo);
      if (!my_strcmp(c->pseudo, pseudo))
	send(c->sock, buffer, my_strlen(buffer), 0);
      ltmp = ltmp->next;
    }
  my_log(__func__, "end", 4);
  return (0);
}

void	send_list(t_client *current, t_chain **salons)
{
  char	*list;

  list = list_salons((*salons));
  my_log(__func__, "list of salons: ", 4);
  my_log(__func__, list, 4);
  my_log(__func__, "asked by: ", 4);
  my_log(__func__, current->pseudo, 4);
}

void	salon_messenger(t_client *c, char *salon, t_chain **clients, int type)
{
  char	str[BUFF_SIZE];
    
  if (type == NOTEXIST)
    {
      sprintf(str, "[SERVER:%s]=> the salon '%s' does not exist", c->room, salon);
      send(c->sock, str, my_strlen(str), 0);
    }
  else if (type == BEFOREMOVETO)
    {
      sprintf(str, "[SERVER:%s]=> %s move to the salon : '%s'",
	      c->room, c->pseudo, salon);
      send_msg_to_all(*clients, str, c->room, c);
      clear_buff(str);
      sprintf(str, "[move:%s]", salon);
      send(c->sock, str, my_strlen(str), 0);
    }
  else if (type == MOVETO)
    {
      sprintf(str, "[SERVER:%s]=> %s just arrived in the '%s' room",
	      c->room, c->pseudo, salon);
      send_msg_to_all(*clients, str, c->room, c);
      clear_buff(str);
      sprintf(str, "[SERVER:%s]=> welcome in the room '%s'", c->room, c->room);
      send(c->sock, str, my_strlen(str), 0);
    }
}
