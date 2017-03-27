/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Sun Mar 26 12:43:08 2017 gastal_r
*/

#include      "lemipc.h"

int		print_usage(void)
{
  printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key \
is a valid path that will be used by ftok\nteam_number is the team number \
assigned to the current player\n");
  return (-1);
}

void		initMap(t_player *map)
{
  int		x;
  int		y;
  int		i;

  x = -1;
  i = -1;
  while (++x < 50) /* 50 == width de la map */
    {
      y = -1;
      while (++y < 50) /* 50 == height de la map */
	{
	  map[i].x = x;
	  map[i].y = y;
	  map[i].team = EMPTY; /* 0 == EMPTY == case vide */
	  ++i;
	}
    }
}

int		initSem(t_struct *desTrucs)
{
  if ((desTrucs->semId = semget(desTrucs->key, 1, IPC_CREAT | SHM_R | SHM_W)) == -1) /* get id ensemble semaphores OU en créée si inexistants */
    return (fprintf(stderr, "Semget failed\n") - 15);
  semctl(desTrucs->semId, 0, SETVAL, 1); /* SETVAL 1 sur semaphore 0 */
  return (0);
}

int		initMsg(t_struct *desTrucs)
{
  if ((desTrucs->msgId = msgget(desTrucs->key, SHM_R | SHM_W)) == -1) /* get id file de messagesQ  */
    if ((desTrucs->msgId = msgget(desTrucs->key, IPC_CREAT | SHM_R | SHM_W)) == -1)  /* créé nouvelle file de messagesQ si inexistante */
      return (fprintf(stderr, "Msgget failed\n") - 15);
  return (0);
}

int		initValues(t_struct *desTrucs, char *path)
{
  if ((desTrucs->key = ftok(path, 0)) == -1) /* get key */
    return (print_usage());
  if ((desTrucs->shmId = shmget(desTrucs->key, sizeof(t_player) * (50 * 50), SHM_R | SHM_W)) == -1) /* alloc segment mem partagée */
    {
      if ((desTrucs->shmId = shmget(desTrucs->key, sizeof(t_player) * (50 * 50), IPC_CREAT | SHM_R | SHM_W)) != -1) /* alloc segment mem partagée si segment pas créé */
	{
	  /* Rentre ici au PREMIER lancement du prog'
	     pour le reinitialiser :	-ipcs -m pour la list des shared mem seg
					-ipcrm [shmid] où le status != dest pour le delete
	   */
	  printf("AVANT SHMAT\n");
	  if ((desTrucs->addr = shmat(desTrucs->shmId, NULL, SHM_R | SHM_W)) == (void *)-1) /* attache la mem partagée au processus  */
	    return (fprintf(stderr, "Shmat failed\n") - 14);
	  else
	    {
	      if (initMsg(desTrucs) == -1
		  || initSem(desTrucs) == -1)
		return (-1);
	      printf("AVANT INITMAP\n");
	      initMap(desTrucs->addr);
	      printf("APRES INITMAP\n");
	      /* TODO : -Créer pion
		        -Fork entre affichage map && reste
			-reste = Déplacement - check si mort
	    }
	  printf("APRES SHMAT\n");
	}
    }

  return (0);
}

int		main(int ac, char *av[])
{
  t_struct	desTrucs;
  t_player	map;

  if (ac != 3)
    return (print_usage());
  printf("AVANT INITVALUES\n");
  if (initValues(&desTrucs, av[1]) == -1)
    return (-1);
  printf("APRES INITVALUES\n");
  printf("Key = %d\nShmId = %d\nAddr = %lld\nmsgId = %d\n", desTrucs.key, desTrucs.shmId, (long long int)desTrucs.addr, desTrucs.msgId);
  return (0);
}
