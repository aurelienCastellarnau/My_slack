/*
** util.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 16:26:55 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:53:23 2017 MASERA Mathieu
*/

#ifndef  _UTIL_H_
#define _UTIL_H_

#include "client.h"

void	clear_buff(char *buffer);
void    clear_room(char *buffer);
void	check_message(t_client *c, char *buffer);
void	message_maker(t_client *c, char *buffer, int type);

#endif /* !_UTIL_H_ */
