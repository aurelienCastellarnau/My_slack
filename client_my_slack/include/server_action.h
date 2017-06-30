/*
** server_action.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:18:39 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 17:01:21 2017 CASTELLARNAU Aurelien
*/

#ifndef  _SERVER_ACTION_H_
# define _SERVER_ACTION_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

int	connect_to(int sock, t_sockaddr_in *sin, char *pseudo);
int	set_fds(fd_set *readfs, t_client *client);
int	send_to_all(t_client *client);
int     receive_on(t_client *client);

#endif	/* !_SERVER_ACTION_H_ */
