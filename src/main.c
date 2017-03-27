/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Mon Mar 27 19:07:21 2017 gastal_r
*/

#include      "lemipc.h"

int		print_usage(void)
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
    {
      y = -1;
      while (++y < 50)
	{
	  i = y * 50 + x;
	  printf("%d", map[i]);
	}
      printf("\n");
    }
}

void    initMap(int *map)
{
  int		x;
  int		y;
  int		i;

  x = -1;
  while (++x < 50)
    {
      y = -1;
      while (++y < 50)
	{
	  i = y * 50 + x;
	  map[i] = EMPTY;
	}
    }
}

int		initSem(t_struct *core)
{
  if ((core->semId = semget(core->key, 1, IPC_CREAT | SHM_R | SHM_W)) == -1) /* get id ensemble semaphores OU en créée si inexistants */
    return (fprintf(stderr, "Semget failed\n") - 15);
  semctl(core->semId, 0, SETVAL, 1); /* SETVAL 1 sur semaphore 0 */
  return (0);
}

int		initMsg(t_struct *core)
{
  if ((core->msgId = msgget(core->key, SHM_R | SHM_W)) == -1) /* get id file de messagesQ  */
    if ((core->msgId = msgget(core->key, IPC_CREAT | SHM_R | SHM_W)) == -1)  /* créé nouvelle file de messagesQ si inexistante */
      return (fprintf(stderr, "Msgget failed\n") - 15);
  return (0);
}

int		initValues(t_struct *core, char *path)
{
  if ((core->key = ftok(path, 0)) == -1) /* get key */
    return (print_usage());
  if ((core->shmId = shmget(core->key, sizeof(t_shared) * (50 * 50), SHM_R | SHM_W)) == -1) /* alloc segment mem partagée */
    {
      if ((core->shmId = shmget(core->key, sizeof(t_shared) * (50 * 50), IPC_CREAT | SHM_R | SHM_W)) != -1) /* alloc segment mem partagée si segment pas créé */
	     {
	      if ((core->addr = shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1) /* attache la mem partagée au processus  */
	       return (fprintf(stderr, "Shmat failed\n") - 14);
        if (initMsg(core) == -1 || initSem(core) == -1)
		     return (-1);
	      initMap(core->addr);
	      displayMap(core->addr);
        // create player
        while (isplayer == true)
        {
          // check msg
          // check mort
          // check poto
          // move
        }
	     }
	   }
     else
     {
       // check msg
       // check sem
       // increase players
       // set team
       // set in map
       // move
       // increase sema
     }
  return (0);
}

int		main(int ac, char *av[])
{
  t_struct	core;

  if (ac != 3)
    return (print_usage());
  core.addr = NULL;
  if (initValues(&core, av[1]) == -1)
    return (-1);
  printf("Key = %d\nShmId = %d\nAddr = %p\nmsgId = %d\n", core.key, core.shmId, core.addr, core.msgId);
  return (0);
}
