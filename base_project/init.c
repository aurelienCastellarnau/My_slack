/*
** init.c for my_slack in /home/aurelien/Documents/test/my_slack_puk
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 21:15:50 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 21:25:04 2017 CASTELLARNAU Aurelien
*/

#include <stdio.h>
#include "libmy.h"
#include "display.h"
#include "component.h"
#include "init.h"

/*
** argument parsing process and program options definition
*/
int	exec(t_option *option)
{
  char	*opt;
  char	*ip;
  char	*port;
  
  opt = option->name;
  if (!my_strcmp(opt, "-h"))
    ((void (*)(void))option->action)();
  if (!my_strcmp(opt, "-v"))
      (*(void (*)(t_chain*))option->action)(option->parameters);
  if (!my_strcmp(opt, "-ip"))
    {
      ip = (char*)((t_link*)((t_chain*)option->parameters)->dictionnary[0])->content;
      (*(char* (*)(char*))option->action)(ip);
    }
  if (!my_strcmp(opt, "-p"))
    {
      port = (char*)((t_link*)((t_chain*)option->parameters)->dictionnary[0])->content;
      (*(int (*)(char*))option->action)(port);
    }
  return (0);
}


/*
** configure programs options
*/
t_chain		*get_opts()
{
  t_chain	*opts;
  t_option	*opt_log;
  t_option	*opt_ip;
  t_option	*opt_port;
  t_option	*opt_help;

  if ((opts = create_chain(free_options_in_chain)) == NULL)
    return (NULL);
  if ((opt_log = new_option(OPTIONNAL, 0, 2, "-v", build_logger)) == NULL)
    return (NULL);
  if ((opt_ip = new_option(OPTIONNAL, 1, 0, "-ip", get_ip)) == NULL)
    return (NULL);
  if ((opt_port = new_option(MANDATORY, 1, 0, "-p", get_port)) == NULL)
    return (NULL);
  if ((opt_help = new_option(OPTIONNAL, 0, 0, "-h", display_help)) == NULL)
    return (NULL);
  if (add_link(&opts, opt_log))
    return (NULL);
  if (add_link(&opts, opt_ip))
    return (NULL);
  if (add_link(&opts, opt_port))
    return (NULL);
  if (add_link(&opts, opt_help))
    return (NULL);
  return (opts);
}

/*
** entry point for parsing and callback of arguments process 
*/
int		init_pgr(int argc, char *argv[])
{
  t_link        *ltmp;
  t_option      *otmp;
  t_chain	*opts;

  opts = get_opts();
  if (parse(1, argc, argv, &opts))
    {
      display_help();
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
  my_log(__func__, "options successfully managed", 3); 
  delete_chain(&opts);
  return (0);
}

/*
** delete singletons
*/
int     end_pgr()
{
  my_log(__func__, "Program my_slack successfully ended.", 3);
  delete_logger();
  delete_ip();
  return (0);
}
