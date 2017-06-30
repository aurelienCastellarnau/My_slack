/*
** server_action.h for my_slack in /home/aurelien/Documents/test/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 21:18:39 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 22:30:23 2017 CASTELLARNAU Aurelien
*/

#ifndef  _SERVER_ACTION_H_
# define _SERVER_ACTION_H_
# define MP 2

int	bind_to(int sock, t_sockaddr_in *sin);
int	listen_to(int sock, int clients);
int	set_fds(fd_set *readfs, int sock, t_chain *clients);
int	manage_transmission(t_chain **clients, t_chain **salons, fd_set *readfs);

#endif	/* !_SERVER_ACTION_H_ */
