 /*
** run_parse.c for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/client_my_slack
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 13:41:09 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 23:41:47 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "struct.h"
#include "init_run_params.h"
#include "server.h"
#include "client.h"
#include "salon.h"
#include "run_action.h"
#include "format_run_parse.h"
#include "run_parse.h"

t_chain		*get_run_opts()
{
  t_chain	*run_opts;
  t_option	*mp_opt;
  t_option	*move_to_opt;
  t_option	*new_salon_opt;
  t_option	*list_salon_opt;

  if ((run_opts = create_chain(free_options_in_chain)) == NULL)
    return (NULL);
  if ((mp_opt = new_option(0, 1, 0, "-mp", private_message)) == NULL)
    return (NULL);
  if ((move_to_opt = new_option(0, 1, 0, "-move", move_to)) == NULL)
    return (NULL);
  if ((new_salon_opt = new_option(0, 1, 0, "-salon", new_salon)) == NULL)
    return (NULL);
  if ((list_salon_opt = new_option(0, 0, 0, "-listsalon", send_list)) == NULL)
    return (NULL);
  if (add_link(&run_opts, mp_opt))
    return (NULL);
  if (add_link(&run_opts, move_to_opt))
    return (NULL);
  if (add_link(&run_opts, new_salon_opt))
    return (NULL);
  if (add_link(&run_opts, list_salon_opt))
    return (NULL);
  return (run_opts);
}

/*
** argument parsing process and program options definition
*/
int		exec_run(t_run_params *parameters)
{
  char		*opt;
  char		*dest;
  t_option	*option;

  option = (t_option*)parameters->option;
  opt = option->name;
  my_log(__func__, "begin", 4);
  if (!my_strcmp(opt, "-mp"))
    {
      dest = (char*)((t_link*)(option->parameters->dictionnary[0])->content);
      my_log(__func__, "execute action of mp", 4);
      my_log(__func__, "pseudo: ", 4);
      my_putstr(dest);
      my_log(__func__, "buffer: ", 4);
      my_putstr(parameters->buffer);
      ((void (*)(t_chain**, char*, char*))option->action)(parameters->clients, dest, parameters->buffer);
      return (CMD);
    }
  if (!my_strcmp(opt, "-move"))
    {
      dest = (char*)((t_link*)(option->parameters->dictionnary[0])->content);
      my_log(__func__, "execute action of move", 3);
      (*(void (*)(t_client*, char*, t_chain**, t_chain**))option->action)(parameters->current, dest, parameters->salons, parameters->clients);
      return (CMD);
    }
  if (!my_strcmp(opt, "-listsalons"))
    {
      my_log(__func__, "client ask for list of salons", 3);
      (*(void (*)(t_client*, t_chain**))option->action)((t_client*)parameters->current, (t_chain**)parameters->salons);
      return (CMD);
    }
  if (!my_strcmp(opt, "-salon"))
    {
      my_log(__func__, "client want to create salon", 3);
      my_putstr(((char*)((t_link*)(option->parameters)->dictionnary[0])->content));
      (*(void (*)(t_chain**, t_run_params*))option->action)(&(option->parameters), parameters);
      return (CMD);
    }
  my_log(__func__, "begin", 4);
  return (0);
}

int		run_parse(t_client *current, char *buffer, t_chain **salons, t_chain **clients)
{
  t_run_params	*parameters;
  t_chain	*run_opts;
  t_link        *ltmp;
  t_option      *otmp;
  char		**argv;
  int		argc;

  my_log(__func__, "begin", 4);
  if ((parameters = init_run_params()) == NULL)
    {
      my_log(__func__, "init run params failed", 1);
      return (PARSE_ERROR);
    }
  if ((run_opts = get_run_opts()) == NULL)
    {
      my_log(__func__, "get opts failed", 4);
      return (PARSE_ERROR);
    }
  if ((parameters->buffer = format_run_opt(buffer)) != NULL && buffer[0] == 45)
    {
      argc = count_word(buffer);
      argv = my_str_to_wordtab(buffer);
      if (parse(0, argc, argv, &run_opts))
	{
	  my_log(__func__, "the program detected an option but found it invalid", 2);
	  return (0);
	}
      else
	{
	  parameters->current = current;
	  parameters->salons = salons;
	  parameters->clients = clients;
	  my_log(__func__, "option recognized and parsed", 4);
	  ltmp = run_opts->first;
	  while (ltmp)
	    {
	      otmp = (t_option*)ltmp->content;
	      parameters->option = otmp;
	      if (otmp->to_execute)
		{
		  my_log(__func__, "execute", 4);
		  if (exec_run(parameters) == CMD)
		    return (CMD);
		}
	      ltmp = ltmp->next;
	    }
	}
    }
  my_log(__func__, "end", 4);
  return (0);
}
