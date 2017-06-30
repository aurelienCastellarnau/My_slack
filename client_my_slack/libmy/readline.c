/*
** readline.c for my_FTL in /home/aurelien/aurelien/ftl/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Nov 11 15:36:20 2016 CASTELLARNAU Aurelien
** Last update Sat Nov 12 10:34:35 2016 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include <unistd.h>

/*
** Cette fonction permet de récuper une ligne
** de moins de 50 caractères sur l'entrée standard.
** La fonction ne prend pas de paramètre et renvoit une chaîne
** allouée (pensez a free()).
*/
char		*readline(void)
{
  ssize_t	ret;
  char		*buff;

  if ((buff = malloc((50 + 1) * sizeof(char))) == NULL)
    return (NULL);
  if ((ret = read(0, buff, 50)) > 1)
    {
      buff[ret - 1] = '\0';
      return (buff);
    }
  free(buff);
  return (NULL);
}
