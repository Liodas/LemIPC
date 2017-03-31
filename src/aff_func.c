/*
** aff_func.c for PSU_2016_lemipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 30 23:04:16 2017 gastal_r
** Last update	Thu Mar 30 23:05:37 2017 gastal_r
*/

#include    "lemipc.h"

int		printUsage(void)
{
  printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key \
is a valid path that will be used by ftok\nteam_number is the team number \
assigned to the current player\n");
  return (-1);
}

void		displayMap(int *map)
{
  int		x;
  int		y;
  int		i;

  x = -1;
  while (++x < 50)
    printf("-");
  printf("-\n");
  x = -1;
  while (++x < 50)
    {
      printf("|");
      y = -1;
      while (++y < 50)
	{
	  i = y * 50 + x;
	  map[i] != 0 ? printf("%d", map[i]) : printf(" ");
	}
      printf("|\n");
    }
  x = -1;
  while (++x < 50)
    printf("-");
  printf("-\n");
}

void			timeDislayMap(t_struct *core)
{
  static clock_t	t1 = -10000;
  clock_t		t2;

  t2 = clock();
  if (t2 - t1 >= 10000)
    {
      system("clear");
      //printf("\033[2J\033[1;1H");
      displayMap(core->addr->map);
      printf("teams = %d\n", core->addr->teams);
      t1 = clock();
    }
}
