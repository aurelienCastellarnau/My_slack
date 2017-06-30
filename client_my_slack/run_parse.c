 /*
** run_parse.c for my_slack in /home/aurelien/Documents/test/mat_my_slack/castel_a/client_my_slack
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 22 13:41:09 2017 CASTELLARNAU Aurelien
** Last update Wed Apr 26 11:43:49 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"
#include "client.h"
#include "salon.h"
#include "run_action.h"
#include "run_parse.h"

t_chain		*get_run_opts()
{
  t_chain	*run_opts;
  t_option	*mp_opt;
  t_option	*move_to_opt;
  t_option	*new_salon_opt;

  if ((run_opts = create_chain(free_options_in_chain)) == NULL)
    return (NULL);
  if ((mp_opt =  new_option(0, 1, 0, "-mp", private_message)) == NULL)
    return (NULL);
  if ((move_to_opt = new_option(0, 1, 0, "-move", move_to)) == NULL)
    return (NULL);
  if ((new_salon_opt = new_option(0, 1, 0, "-salon", new_salon)) == NULL)
    return (NULL);
  if (add_link(&run_opts, mp_opt))
    return (NULL);
  if (add_link(&run_opts, move_to_opt))
    return (NULL);
  if (add_link(&run_opts, new_salon_opt))
    return (NULL);
  return (run_opts);
}

int	format_run_opt(char *buffer)
{
  my_log(__func__, "begin", 4);
  if (!my_strncmp(buffer, "[mp:", 4))
    {
      buffer[0] = 45;
      buffer[3] = ' ';
    }
  else if (!my_strncmp(buffer, "[move:", 6))
    {
      buffer[0] = 45;
      buffer[5] = ' ';
    }
  else if (!my_strncmp(buffer, "[salon:", 7))
    {
      buffer[0] = 45;
      buffer[6] = ' ';
    }
  else
    {
      my_log(__func__, "this is not an option", 3);
      return (0);
    }
  my_log(__func__, "end", 4);
  return (0);
}

/*
** argument parsing process and program options definition
*/
int		exec_run(t_option *option, t_chain **salons, t_chain **clients)
{
  char		*opt;
  t_chain	*guests;

  opt = option->name;
  guests = create_chain(free_clients);
  if (!my_strcmp(opt, "-mp"))
    ((void (*)(void))option->action)();
  if (!my_strcmp(opt, "-move"))
    {
      (*(void (*)(t_chain*))option->action)(option->parameters);
    }
  if (!my_strcmp(opt, "-salon"))
    {
      my_log(__func__, "a client want to add a salon", 3);
      if ((list_guests(&(option->parameters), &guests, clients)) == PARSE_ERROR)
	return (PARSE_ERROR);
      (*(void (*)(t_chain**, t_chain**, t_chain**))option->action)(&(option->parameters), salons, &guests);
    }
  return (0);
}

int		run_parse(char *buffer, t_chain **salons)
{
  t_chain	*run_opts;
  t_link        *ltmp;
  t_option      *otmp;
  char		**argv;
  int		argc;

  my_log(__func__, "begin", 4);
  if ((run_opts = get_run_opts()) == NULL)
    return (SOCKET_ERROR);
  if (format_run_opt(buffer))
    {
      argv = my_str_to_wordtab(buffer);
      argc = my_arrlen((void**)argv);
      // ici parse ne peut pas gérer la récupération de l'élément après [opt:
      if (parse(argc, argv, &run_opts))
	{
	  // display client options help
	  my_log(__func__, "the program detected an option but found it invalid", 2);
	  return (0);
	}
      else
	{
	  ltmp = run_opts->first;
	  while (ltmp)
	    {
	      otmp = (t_option*)ltmp->content;
	      if (otmp->to_execute)
		exec_run(otmp, salons, clients);
	      ltmp = ltmp->next;
	    }
	}
    }
  my_log(__func__, "end", 4);
  return (0);
}
