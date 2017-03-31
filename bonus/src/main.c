/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Fri Mar 31 16:34:53 2017 gastal_r
*/

#include      "lemipc.h"

void		freeIPCS(t_struct *core)
{
  char *str;

  str = (char *) calloc(10, 1);
  sprintf(str, "ipcrm -m %d", core->shmId);
  system(str);
  sprintf(str, "ipcrm -s %d", core->semId);
  system(str);
  sprintf(str, "ipcrm -q %d", core->msgId);
  system(str);
  free(str);
}

int		checkNewTeam(t_struct *core, int idTeam)
{
  int		i;

  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (core->addr->map[i] == idTeam)
      return (0);
  return (1);
}

void  semOperation(t_struct *core, int op)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = op;
  semop(core->semId, &sops, 1);
}

int  checkPressedKey(t_graph *graph)
{
  sfEvent event;

  while (sfRenderWindow_pollEvent(graph->win, &event))
  {
    if (event.type == sfEvtClosed ||
       (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
      {
        sfRenderWindow_close(graph->win);
        return (0);
      }
  }
  return (1);
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
