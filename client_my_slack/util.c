/*
** util.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 16:28:08 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:53:55 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "util.h"
#include "server.h"
#include "client.h"
#include "const.h"
#include <stdio.h>

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

void	check_message(t_client *c, char *buffer)
{
  char	room[20];
  int	i;
  int	j;
  
  i = 6;
  j = 0;
  if (my_strncmp(buffer, "[move:", 6) == 0)
    {
      clear_room(c->room);
      while (buffer[i] != ']')
	{
	  room[j] = buffer[i];
	  i++;
	  j++;
	}
      
      my_strcpy(c->room, room); 
    }
}
