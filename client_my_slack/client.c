/*
** client.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 11:49:48 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:17:24 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "util.h"
#include "client.h"
#include "server_action.h"

t_client	*init_client()
{
  t_client	*c;

  if ((c = malloc(sizeof(t_client))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  c->sin = NULL;
  c->sock = 0;
  c->pseudo = NULL;
  my_strcpy(c->room, "mainRoom");
  return (c);
}

void	delete_client(t_client **c)
{
  if (c == NULL || (*c) == NULL)
    return;
  if ((*c)->pseudo != NULL)
    free((*c)->pseudo);
  /* ?
  **  if (c->sin != NULL)
  **    free(c->sin);
  */
  free((*c));
}

int		set_pseudo(t_chain *parameters, t_client **c)
{
  t_link	*ltmp;
  
  if (c == NULL || (*c) == NULL)
    {
      my_log(__func__, "client undefined", 1);
      return (RUNTIME_ERROR);
    }
  if (parameters == NULL
      || (ltmp = (t_link*)parameters->dictionnary[0]) == NULL)
    {
      my_log(__func__, "parameters undefined", 1);
      return (RUNTIME_ERROR);
    }
  (*c)->pseudo = my_strdup((char*)ltmp->content);
  return (0);
}
