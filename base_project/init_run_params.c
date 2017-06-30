/*
** init_run_params.c for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 26 13:47:43 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:35:00 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"
#include "struct.h"
#include "server.h"
#include "client.h"
#include "init_run_params.h"

/*
** initialise structure for passing runtime parsing arguments
*/
t_run_params	*init_run_params()
{
  t_run_params	*params;

  if ((params = malloc(sizeof(*params))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  params->buffer = NULL;
  params->current = NULL;
  params->salons = NULL;
  params->clients = NULL;
  params->option = NULL;
  return (params);
}
