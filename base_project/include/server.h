/*
** server.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sun Apr 16 15:55:07 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:17:26 2017 CASTELLARNAU Aurelien
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

#define SOCKET_ERROR -1
#define DISCONNECTED -1
#define CONNECTED 0
#define BROADCAST 1
#define CLIENT 2
#define REGISTERED 1
#define REGISTER_ERROR -1
#define MAX_CLIENT 30
#define PORT 3000
#define ADDR_IP "127.0.0.0"
#define BUFF_SIZE 1025
#define NOTEXIST 0
#define BEFOREMOVETO 1
#define MOVETO 2

typedef struct		s_sockaddr_in
{
  short			sin_family;
  unsigned short	sin_port;
  struct in_addr	sin_addr;
  char			sin_zero[8];
}			t_sockaddr_in;

typedef struct		sockaddr t_sockaddr;

int			init_server();
int			init_sock(int *sock, t_chain **clients, t_chain **salons);
int			server_talking(t_chain **clients);

#endif   /* !_SERVER_H_ */
