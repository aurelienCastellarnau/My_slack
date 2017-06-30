/*
** component.c for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:03:25 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 19 21:49:09 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "server.h"
#include "component.h"

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

  if ((addr_in = malloc(sizeof(t_sockaddr_in))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  if ((addr_in->sin_addr.s_addr = inet_addr("127.0.0.1")) == (in_addr_t)(-1))
    {
      my_log(__func__, "innet addr", 1);
      return (NULL);
    }
  else
    my_log(__func__, "inet_addr ok", 3);
  addr_in->sin_family = AF_INET;
  addr_in->sin_port = htons(3000);
  return (addr_in);
}
