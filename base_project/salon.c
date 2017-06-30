/*
** salon.c for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/LibC/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 19:00:22 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:33:52 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "init_run_params.h"
#include "salon.h"
#include "util.h"

t_salon		*init_salon(t_chain **salons)
{
  t_salon	*salon;
  
  if ((salon = malloc(sizeof(*salon))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  my_strcpy(salon->name, "mainRoom");
  salon->clients = create_chain(NULL);
  if (add_link(salons, salon))
    return (NULL);
  return (salon);
}

t_salon		*new_salon(t_chain **parameters, t_run_params *run_params)
{
  t_salon	*salon;
  char		buffer[BUFF_SIZE];

  my_log(__func__, "begin", 4);
  if ((run_params == NULL ||
       parameters == NULL || parameters == NULL))
    {
      my_log(__func__, "salons or parameters are empty", 1);
      return (NULL);
    }
  if ((salon = malloc(sizeof(*salon))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  my_strcpy(salon->name,((char*)((t_link*)(*parameters)->dictionnary[0])->content));
  if ((salon->clients = create_chain(NULL)) == NULL)
    {
      my_log(__func__, "failed init salon clients", 1);
      return (NULL);
    }
  if (add_link(run_params->salons, salon))
    {
      my_log(__func__, "failed init salon clients", 1);
      return (NULL);
    }
  my_log(__func__, "end", 4);
  sprintf(buffer, "[SERVER:toAll]=> A new room '%s' got created", salon->name);
  send_msg_to_all((*run_params->clients), buffer, NULL, NULL);
  return (NULL);
}

void		free_salons(t_chain **salons)
{
  t_link	*ltmp;
  t_salon	*stmp;

  if (salons == NULL)
    {
      my_log(__func__, "the liste of salon is empty", 2);
      return;
    }
  ltmp = (*salons)->first;
  while (ltmp)
    {
      stmp = (t_salon*)ltmp->content;
      if (stmp != NULL)
	  free(stmp);
      ltmp = ltmp->next;
    }
}

char		*list_salons(t_chain *salons)
{
  t_link	*ltmp;
  char		*salon;
  char		*list;

  if (salons == NULL || salons->first == NULL)
    {
      my_log(__func__, "no salons available", 2);
      return (NULL);
    }
  ltmp = salons->first;
  while (ltmp)
    {
      salon = (char*)((t_salon*)ltmp->content)->name;
      list = my_strcat(list, "\n-");
      list = my_strcat(list, salon);
      ltmp = ltmp->next;
    }
  return (list);
}
