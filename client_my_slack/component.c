/*
** component.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:03:25 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 23:22:12 2017 MASERA Mathieu
*/

#include "libmy.h"
#include "client.h"
#include "server.h"
#include "component.h"
#include "const.h"

int		get_socket()
{
  int		tmp_sock;
  
  if ((tmp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      my_log(__func__, "socket init", 1);
      return (SOCKET_ERROR);
    }
  else
    my_log(__func__, "socket init ok", 3);
  return(tmp_sock);
}

t_sockaddr_in	*get_addrin()
{
  t_sockaddr_in *addr_in;
  char		*ip;
  int		port;

  if ((ip = get_ip(NULL)) == NULL)
    return (NULL);
  if ((port = get_port(NULL)) == 0)
    return (NULL);
  if ((addr_in = malloc(sizeof(t_sockaddr_in))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  if ((addr_in->sin_addr.s_addr = inet_addr(ip)) == (in_addr_t)(-1))
    {
      my_log(__func__, "innet addr", 1);
      return (NULL);
    }
  else
    my_log(__func__, "inet_addr ok", 3);
  addr_in->sin_family = AF_INET;
  addr_in->sin_port = htons(port);
  return (addr_in);
}

char            *get_ip(char *ip)
{
  static char   *i;
  if (i == NULL && ip != NULL)
    i = my_strdup(ip);
  if (i == NULL)
    return (NULL);
  return (i);
}

int             get_port(char *port)
{
  static int    p;

  if (p == 0 && port != NULL)
    p = my_getnbr(port);
  if (p == 0)
    return (0);
  return (p);
}
