/*
** util.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 16:28:08 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 19 16:29:10 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "util.h"

void	clear_buff(char *buffer)
{
  while ((*buffer) != 0)
    {
      (*buffer) = 0;
      ++buffer;
    }
}
