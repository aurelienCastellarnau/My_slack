/*
** main.c for demoLib in /home/aurelien/Documents/demoLib/libmy_extended
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr  5 11:44:31 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 19:45:48 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"
#include "struct.h"
#include "client.h"
#include "server_action.h"
#include "init.h"
#include "server.h"

/*
** Entry point
*/
int		main(int argc, char *argv[])
{
  t_client	*c;

  if ((c = init_client()) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (0);
    }
  if (init_pgr(argc, argv, &c))
    return (1);
  if (init_server(&c))
      return (1);
  if (end_pgr(&c))
    return (1);
  return (0);
}
