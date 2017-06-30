/*
** util.c for my_slack in /home/aurelien/Documents/test/client
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 15:56:44 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 19 16:46:49 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "util.h"

void	clear_buff(char *buffer)
{
  while ((*buffer) != '\0')
    {
      (*buffer) = 0;
      ++buffer;
    }
}
