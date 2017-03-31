/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Fri Mar 31 00:44:43 2017 gastal_r
*/

#include      "lemipc.h"

void		checkNewTeam(t_struct *core, int idTeam)
{
  int		i;

  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (core->addr->map[i] == idTeam)
      return ;
  core->addr->teams += 1;
}

void  semOperation(t_struct *core, int op)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = op;
  semop(core->semId, &sops, 1);
}

int		main(int ac, char *av[])
{
  t_struct	core;

  if (ac != 3)
    return (printUsage());
  core.addr = NULL;
  srand(time(NULL));
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  return (0);
}
