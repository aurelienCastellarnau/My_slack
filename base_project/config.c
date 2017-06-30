/*
** config.c for my_slack in /home/aurelien/Documents/test/my_slack_puk
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 21:17:35 2017 CASTELLARNAU Aurelien
** Last update Sat Apr 15 22:40:21 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "config.h"

/*
** Config for the my_slack setup from program arguments
*/

void            config(t_chain *parameters)
{
  int           port;

  my_putstr("\nThe address is set to: ");
  my_putstr((char*)((t_link*)parameters->dictionnary[0])->content);
  my_putstr("\nThe port is set to: ");
  port = my_getnbr((char*)((t_link*)parameters->dictionnary[1])->content);
  my_put_nbr(port);
  my_putchar('\n');
}
