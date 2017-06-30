/*
** display.c for my_slack in /home/aurelien/Documents/test/my_slack_puk
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 21:18:14 2017 CASTELLARNAU Aurelien
** Last update Tue Apr 25 00:45:39 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "display.h"

/*
** General program display functions
*/

void    display_help()
{
  my_putstr("\n--- HOW TO USE ---\n");
  my_putstr("\nlegend: '!' = mandatory\n");
  my_putstr("\nmandatory: -pseudo [your pseudo]!");
  my_putstr("\nOptional: -v [level] / with level = debug|info|warning|error\n");
  my_putstr("\nOptional: -addr [address]! [port]!\n");
  my_putstr("\nOptional: -h: display usage\n");
}

