/*
** init.h for my_slack in /home/aurelien/Documents/test/my_slack_puk/include
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 21:07:30 2017 CASTELLARNAU Aurelien
** Last update Tue Apr 25 00:13:01 2017 CASTELLARNAU Aurelien
*/

#ifndef _INIT_H_
#define _INIT_H_

#include "libmy.h"

int	init_pgr(int argc, char *argv[], t_client **c);
int	end_pgr(t_client **c);

#endif /* !_INIT_H_ */
