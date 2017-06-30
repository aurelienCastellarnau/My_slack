/*
** listen_clients.h for my_slack in /home/aurelien/Documents/my_slack/depot/castel_a/base_project
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Apr 27 22:27:12 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:18:07 2017 CASTELLARNAU Aurelien
*/

#ifndef  _LISTEN_CLIENTS_H_
# define _LISTEN_CLIENTS_H_

int	listen_clients(t_chain **clients,
			t_chain **salons,
			t_link *ltmp,
			t_client *c);
int	disconnect_one(t_chain **clients, t_client *c, t_link *ltmp, char *buffer);

#endif   /* !_LISTEN_CLIENTS_H_ */
