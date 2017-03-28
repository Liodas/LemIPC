/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Tue Mar 28 17:12:24 2017 gastal_r
*/

#include      "lemipc.h"

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
    {
      y = -1;
      while (++y < 50)
	{
	  i = y * 50 + x;
	  printf("%d ", map[i]);
	}
      printf("\n");
    }
}

int		checkAround(t_struct *core, t_player player, int nbEnem, int inRange)
{
  int		i;
  int		x;
  int		y;

  y = player.y - inRange - 1;
  while (++y <= player.y + inRange)
    {
      x = player.x - inRange - 1;
      while (++x <= player.x + inRange)
	{
	  i = y * 50 + x;
	  if (i < 2500 && core->addr->map[i] != EMPTY &&
	      core->addr->map[i] != player.team)
	    nbEnem++;
	}
    }
  return (nbEnem > 1 ? 0 : 1);
}

void  semOperation(t_struct *core, int op)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = op;
  semop(core->semId, &sops, 1);
}

void  i_die_msg(t_struct *core, t_player *player)
{
  t_msg msg;

  bzero(&msg, sizeof(t_msg));
  msg.mtype = player->id + 1;
  sprintf(msg.str, "Decremente %d", player->id);
  msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
  printf("message sended\n");
  semOperation(core, -1);
  core->addr->players--;
}

void  mainloop(t_struct *core, t_player *player)
{
  t_msg msg;

  while (1)
  {
    sleep(1);
    bzero(&msg, sizeof(t_msg));
    msgrcv(core->msgId, &msg, sizeof(t_msg), player->id, IPC_NOWAIT);
    printf("playerid=%d %s\n",player->id, msg.str);
    if (strlen(msg.str) > 0)
      player->id--;
    printf("sem=%d\n", semctl(core->semId, 0, GETVAL));
    if (semctl(core->semId, 0, GETVAL) == player->id)
    {
      printf("ITS MY TURN BITCHES\n");
      core->addr->map[5 * 50 + 38] = 7;
      core->addr->map[4 * 50 + 37] = 7;
      if (!checkAround(core, *player, 0, 1))
      {
        i_die_msg(core, player);
        return;
      };
      if (semctl(core->semId, 0, GETVAL) == core->addr->players)
      {
        semOperation(core, -core->addr->players + 1);

      }
      else
        semOperation(core, 1);
    }
  }
}

int		main(int ac, char *av[])
{
  t_struct	core;

  if (ac != 3)
    return (printUsage());
  core.addr = NULL;
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  return (0);
}
