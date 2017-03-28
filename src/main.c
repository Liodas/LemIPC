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

int		checkAround(t_struct *core, t_player player,
			 int nbEnem, int range)
{
  int		i;
  int		x;
  int		y;

  y = player.y - range - 1;
  while (++y < range * 2 + 1)
    {
      x = player.x - range - 1;
      while (++x < range * 2 + 1)
	{
	  i = y * 50 + x;
	  if (core->addr->map[i] && core->addr->map[i] != EMPTY &&
	      core->addr->map[i] != player.team
	      && y != player.y && x != player.x)
	    nbEnem++;
	  printf("X = %d ||| Y = %d\n", x, y);
	}
    }
  return (nbEnem > 2 ? - 1 : 0);
}

void  mainloop(t_struct *core, int idTeam)
{
  t_msg msg;
  t_player player;

  initNewPlayer(core, &player, idTeam);
  while (checkAround(core, player, 0, 1))
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

int		main(int ac, char *av[])
{
  t_struct	core;

  if (ac != 3)
    return (printUsage());
  core.addr = NULL;
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  
  printf("Key = %d\nShmId = %d\nAddr = %p\nmsgId = %d\n", core.key, core.shmId, core.addr->map, core.msgId);
  return (0);
}
