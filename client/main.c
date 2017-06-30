/*
** main.c for demoLib in /home/aurelien/Documents/demoLib/libmy_extended
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr  5 11:44:31 2017 CASTELLARNAU Aurelien
** Last update Sun Apr 16 17:33:36 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"
#include "display.h"
#include "config.h"
#include "init.h"
#include "server.h"

/*
** Entry point
*/
int		main(int argc, char *argv[])
{
  if (init_pgr(argc, argv))
    {
      my_log(__func__, "init program failed", 1);
      return (1);
    }
  if (init_server())
    {
      my_log(__func__, "init server failed", 1);
      return (1);
    }
  if (end_pgr())
    return (1);
  return (0);
}
