/*
** init.c for my_slack in /home/aurelien/Documents/test/my_slack_puk
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 21:15:50 2017 CASTELLARNAU Aurelien
** Last update Sun Apr 16 20:51:31 2017 CASTELLARNAU Aurelien
*/

#include <stdio.h>
#include "libmy.h"
#include "config.h"
#include "display.h"
#include "init.h"

/*
** argument parsing process and program options definition
*/

int     exec(t_option *option)
{
  char  *opt;

  opt = option->name;
  if (!my_strcmp(opt, "-h"))
    ((void (*)(void))option->action)();
  if (!my_strcmp(opt, "-v") || !my_strcmp(opt, "-addr"))
    {
      (*(void (*)(t_chain*))option->action)(option->parameters);
      // Switch to my_log to make this pre-load logging disappear
      devlog(__func__, "callback of option: ", 3);
      devlog(__func__, opt, 3);
    }
return (0);
}


/*
** ./libmy/logger.c
** ./config.c
** ./display.c
*/
t_chain *get_opts()
{
  t_chain       *opts;
  t_option      *opt_log;
  t_option      *opt_conf;
  t_option      *opt_help;

  if ((opts = create_chainf(free_options_in_chain)) == NULL)
    return (NULL);
  if ((opt_log = new_option(0, 0, 2, "-v", build_logger)) == NULL)
    return (NULL);
  if ((opt_conf = new_option(0, 2, 0, "-addr", config)) == NULL)
    return (NULL);
  if ((opt_help = new_option(0, 0, 0, "-h", display_help)) == NULL)
    return (NULL);
  if ((opt_log->parameters = create_chain()) == NULL)
    return (NULL);
  if ((opt_conf->parameters = create_chain()) == NULL)
    return (NULL);
  if (add_link(&opts, opt_log))
    return (NULL);
  if (add_link(&opts, opt_conf))
    return (NULL);
  if (add_link(&opts, opt_help))
    return (NULL);
  // Switch to my_log to make this pre-load logging disappear
  devlog(__func__, "Program's options are loaded", 3);
  return (opts);
}

int		init_pgr(int argc, char *argv[])
{
  t_link        *ltmp;
  t_option      *otmp;
  t_chain	*opts;

  opts = get_opts();
  if (parse(argc, argv, &opts))
    {
      display_help();
      // Switch to my_log to make this pre-load logging disappear
      devlog(__func__, "Error Parsing arguments, the programme must quit.", 1);
      return (1);
    }
  else
    {
      ltmp = opts->first;
      while (ltmp)
	{
	  otmp = ((t_option*)ltmp->content);
	  if (otmp->to_execute)
	    exec(otmp);
	  ltmp = ltmp->next;
	}
    }
  delete_chainf(&opts);
  return (0);
}

int     end_pgr()
{
  // Switch to my_log to make this pre-load logging disappear
  devlog(__func__, "Program my_slack successfully ended.", 3);
  delete_logger();
  return (0);
}
