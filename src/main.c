/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Tue Mar 28 00:32:58 2017 gastal_r
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

void    initMap(t_struct *core)
{
  int		x;
  int		y;
  int		i;

  x = -1;
  //core->addr->map = malloc(sizeof(int) * 50 * 50);
  while (++x < 50)
    {
      y = -1;
      while (++y < 50)
	{
	  i = y * 50 + x;
	  core->addr->map[i] = EMPTY;
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
  {
    printf("Creation du msgID\n");
    if ((core->msgId = msgget(core->key, IPC_CREAT | SHM_R | SHM_W)) == -1)  /* créé nouvelle file de messagesQ si inexistante */
      return (fprintf(stderr, "Msgget failed\n") - 15);
    }
  return (0);
}

int   is_alive()
{
  return (1);
}

void  mainloop(t_struct *core)
{
  t_msg msg;
  t_player player;

  player.id = core->addr->players + 1;
  core->addr->players += 1;
  while (is_alive())
  {
    if (1)
    {
      sleep(1);
      bzero(&msg, sizeof(t_msg));
      msg.mtype = 666;
      sprintf(msg.str, "Bonsoir %d", player.id);
      msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
      //msgctl(core->msgId, IPC_RMID, NULL);
      printf("message sended\n");
      // check msg
      // check sem
      // increase players
      // set team
      // set in map
      // move
      // increase sema
    }
  }
}

int		initValues(t_struct *core, char *path)
{
  t_msg msg;
  int go_on;

  go_on = 1;
  if ((core->key = ftok(path, 0)) == -1) /* get key */
    return (print_usage());
  initMsg(core);
  printf("msgid %d\n", core->msgId);
  if ((core->shmId = shmget(core->key, sizeof(t_shared) * 50 * 50, SHM_R | SHM_W)) == -1) /* alloc segment mem partagée */
    {
      if ((core->shmId = shmget(core->key, sizeof(t_shared) * 50 * 50, IPC_CREAT | SHM_R | SHM_W)) != -1) /* alloc segment mem partagée si segment pas créé */
	     {
         printf("shmid %d\n", core->shmId);
         if ((core->addr = shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1) /* attache la mem partagée au processus  */
          return (fprintf(stderr, "Shmat failed\n") - 14);
        printf("%p\n", core->addr);
        if (initSem(core) == -1)
		     return (-1);
	      initMap(core);
	      displayMap(core->addr->map);
        // create player
        core->addr->players = 1;
        core->addr->teams = 1;
        while (go_on)
        {
          sleep(1);
          printf("players= %d  teams=%d\n", core->addr->players, core->addr->teams);
          bzero(&msg, sizeof(t_msg));
          printf("Created msg %d\n", core->msgId);
          msgrcv(core->msgId, &msg, sizeof(t_msg), 666, IPC_NOWAIT);
          printf("%s\n", msg.str);

          // check msg
          // check mort
          // check poto
          // move
        }
      }
	   }
     else
     {
       //core->addr->teams += 1;
       printf("%p\n", core->addr);
       printf("shmid %d\n", core->shmId);
       if ((core->addr = shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1) /* attache la mem partagée au processus  */
        return (fprintf(stderr, "Shmat failed\n") - 14);
       printf("%p\n", core->addr);
       displayMap(core->addr->map);
       mainloop(core);
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
  printf("Key = %d\nShmId = %d\nAddr = %p\nmsgId = %d\n", core.key, core.shmId, core.addr->map, core.msgId);
  return (0);
}
