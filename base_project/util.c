/*
** util.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 16:28:08 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:33:26 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 14:41:01 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "util.h"

void    clear_buff(char *buffer)
{
  int	i;

  i = 0;
  while (i < BUFF_SIZE)
    {
      *buffer = '\0';
      buffer++;
      i++;
    }
  buffer = buffer - i;
}

void    clear_room(char *buffer)
{
  int	i;

  i = 0;
  while (i < 20)
    {
      *buffer = '\0';
      buffer++;
      i++;
    }
  buffer = buffer - i;
}

void	send_msg_to_all(t_chain *clients, char *str, char *room, t_client *from)
{
  t_link	*ltmp;
  t_client	*c;
  char		buffer[100];

  my_log(__func__, "send message to all", 4);
  if (clients == NULL || clients->first == NULL)
    {
      my_log(__func__, "clients list is empty", 2);
      return;
    }
  ltmp = clients->first;
  while (ltmp)
    {
      c = (t_client*)ltmp->content;
      if (from == NULL || (c->sock != from->sock && !my_strcmp(c->room, room)))
	{
	  sprintf(buffer, "Send message from to %s", c->pseudo);
	  my_log(__func__, buffer, 4);
      	  if (send(c->sock, str, my_strlen(str), 0) < 0)
	    my_log(__func__, "error sending message", 1);
	}
      ltmp = ltmp->next;
    }
  clear_buff(str);
}

void	message_maker(t_client *c, char *buffer, int type)
{
  char	str[BUFF_SIZE];

  if (type == DISCONNECTED)
    {
      clear_buff(buffer);
      sprintf(buffer, "[SERVER:%s]=> %s got disconnected.", c->room,  c->pseudo);
    }
  if (type == CONNECTED)
    {
      clear_buff(buffer);
      sprintf(buffer, "[SERVER:%s]=> %s joined this chat's room", c->room,
	      c->pseudo);
    }
  if (type == BROADCAST)
    {
      my_strcpy(str, buffer);
      clear_buff(buffer);
      sprintf(buffer, "[SERVER:toAll]=> %s",str);
    }
  if (type == CLIENT)
    {
      my_strcpy(str, buffer);
      clear_buff(buffer);
      sprintf(buffer, "[%s:%s]=> %s",c->pseudo, c->room, str);
    }
}
