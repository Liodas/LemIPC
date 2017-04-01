/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Sat Apr 01 17:31:23 2017 gastal_r
*/

#include      "lemipc.h"

void		freeIPCS(t_struct *core)
{
  if (shmctl(core->shmId, IPC_RMID, 0) < 0)
    perror("");
  if (semctl(core->semId, 0, IPC_RMID) < 0)
    perror("");
  if (msgctl(core->msgId, IPC_RMID, 0) < 0)
    perror("");
  system("killall lemipc");
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

void		semOperation(t_struct *core, int op)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = op;
  semop(core->semId, &sops, 1);
}

int		checkPressedKey(t_graph *graph)
{
  sfEvent	event;

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
  int		idTeam;

  if (ac != 3)
    return (printUsage());
  core.addr = NULL;
  srand(time(NULL));
  if ((idTeam = atoi(av[2])) <= 0)
    return (printUsage());
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  return (0);
}
