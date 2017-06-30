/*
** component.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:12:21 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:24:02 2017 CASTELLARNAU Aurelien
*/

#ifndef  _COMPONENT_H_
# define _COMPONENT_H_

#include "server.h"

int		get_socket();
t_sockaddr_in	*get_addrin();
char		*get_ip(char *ip);
void		delete_ip();
int		get_port(char *port);

#endif   /* !_COMPONENT_H_ */
