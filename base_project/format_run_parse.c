/*
** util_run_parse.c for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Apr 27 21:41:54 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 22:09:31 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

int	search_and_format(char * buffer)
{
  if (!my_strncmp(buffer, "[mp:", 4))
    buffer[3] = ' ';
  else if (!my_strncmp(buffer, "[move:", 6))
    buffer[5] = ' ';
  else if (!my_strncmp(buffer, "[salon:", 7))
    buffer[6] = ' ';
  else if (!my_strncmp(buffer, "[listsalon]", 11))
    buffer[10] = ' ';
  else if (!my_strncmp(buffer, "[help]", 6))
    buffer[5] = ' ';
  else
    {
      my_log(__func__, "this is not an option", 3);
      return (1);
    }
  return (0);
 }

char	*format_run_opt(char *buffer)
{
  int	i;
  char	*save;

  i = 0;
  if (search_and_format(buffer))
    return (buffer);
  my_log(__func__, "client sent an option", 3);
  if (!my_strncmp(buffer, "[mp ", 3)
      || !my_strncmp(buffer, "[move ", 5)
      || !my_strncmp(buffer, "[salon ", 6)
      || !my_strncmp(buffer, "[listsalon ", 10)
      || !my_strncmp(buffer, "[help ", 10))
    buffer[0] = 45;
  while (buffer[i] != ']' && buffer[i] != '\0')
    i++;
  if ((save = my_strdup(buffer + i + 1)) == NULL)
    return (NULL);
  buffer[i] = '\0';
  return (save);
}
