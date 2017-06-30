/*
** server.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 16 15:55:07 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 19 11:48:08 2017 CASTELLARNAU Aurelien
*/

#ifndef	 _SERVER_H_
# define _SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define SOCKET_ERROR -1

typedef struct		s_sockaddr_in
{
  short			sin_family;
  unsigned short	sin_port;
  struct in_addr	sin_addr;
  char			sin_zero[8];
}			t_sockaddr_in;

typedef struct		sockaddr t_sockaddr;

int			init_server();

#endif   /* !_SERVER_H_ */
