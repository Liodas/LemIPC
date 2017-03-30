/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Thu Mar 30 18:57:04 2017 gastal_r
*/

#include      "lemipc.h"

int		printUsage(void)
{
  printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key \
is a valid path that will be used by ftok\nteam_number is the team number \
assigned to the current player\n");
  return (-1);
}

void		checkNewTeam(t_struct *core, int idTeam)
{
  int		i;

  i = -1;
  while (++i < 2500)
    if (core->addr->map[i] == idTeam)
      return ;
  core->addr->teams += 1;
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
	  map[i] != 0 ? printf("%d ", map[i]) : printf(" ");
	}
      printf("\n");
    }
}


void	tryMoveDiagonale(t_struct *core, t_player *player, t_player pos, int dir)
{
  if (pos.x < player->x && pos.y < player->y)
    {
      dir == 0 ? tryMoveDown(core, player, dir) :
	tryMoveLeft(core, player, dir);
    }
  else if (pos.x < player->x && pos.y > player->y)
    {
      dir == 0 ? tryMoveUp(core, player, dir) :
	tryMoveLeft(core, player, dir);
    }
  else if (pos.x > player->x && pos.y > player->y)
    {
      dir == 0 ? tryMoveUp(core, player, dir) :
	tryMoveRight(core, player, dir);
    }
  else if (pos.x > player->x && pos.y < player->y)
    {
      dir == 0 ? tryMoveDown(core, player, dir) :
	tryMoveRight(core, player, dir);
    }
}

void  tryMove(t_struct *core, t_player *player, t_player pos)
{
  int dir;

  dir = rand() % 2;
  core->addr->map[player->y * 50 + player->x] = 0;
  if (pos.x == player->x && pos.y < player->y)
    tryMoveDown(core, player, dir);
  else if (pos.x == player->x && pos.y > player->y)
    tryMoveUp(core, player, dir);
  else if (pos.x > player->x && pos.y == player->y)
    tryMoveRight(core, player, dir);
  else if (pos.x < player->x && pos.y == player->y)
    tryMoveLeft(core, player, dir);
  else
    tryMoveDiagonale(core, player, pos, dir);
  core->addr->map[player->y * 50 + player->x] = player->team;
}

void  move(t_struct *core, t_player *player)
{
  t_player pos;
  int enemies;
  int allies;

  enemies = findClosestEnemy(core, player, &pos);
  allies = checkAroundAllies(core, *player, 5);
  if (enemies != 0 && enemies <= allies && allies > 1)
    {
      tryMove(core, player, pos);
    }
  else
    {
      if (findClosestAllies(core, player, &pos) > 0)
        tryMove(core, player, pos);
    }
}

int		checkAround(t_struct *core, t_player player, int inRange)
{
  int		i;
  int		x;
  int		y;
  t_player tmp;

  tmp.x = player.x;
  tmp.y = player.y;
  y = player.y - inRange - 1;
  while (++y <= player.y + inRange)
    {
      x = player.x - inRange - 1;
      while (++x <= player.x + inRange)
	{
	  i = y * 50 + x;
	  if (y >= 0 && x >= 0 && i < 2500 && core->addr->map[i] != EMPTY &&
	      core->addr->map[i] != player.team)
	    {
	      tmp.team = core->addr->map[i];
	      if (checkAroundAllies(core, tmp, 1) >= 2)
		return (2);
	    }
	}
    }
  return (0);
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

  //printf("tant pis je meurs %d %d\n", player->id ,core->addr->players);
  if (player->id != core->addr->players)
  {
    bzero(&msg, sizeof(t_msg));
    msg.mtype = player->id + 1;
    sprintf(msg.str, "%d Died", player->id);
    msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
  }
  if (player->id == core->addr->players)
  {
    semOperation(core, -(player->id) + 1);
    core->addr->players--;
  }
  core->addr->map[player->y * 50 + player->x] = 0;
}

void  mainloop(t_struct *core, t_player *player)
{
  t_msg msg;

  while (1)
    {
      //usleep(50000);
      bzero(&msg, sizeof(t_msg));
      msgrcv(core->msgId, &msg, sizeof(t_msg), player->id, IPC_NOWAIT);
      //printf("playerid=%d %s\n",player->id, msg.str);
      //printf("sem=%d\n", semctl(core->semId, 0, GETVAL));
      if (strlen(msg.str) > 0)
	    {
        if (core->addr->players != player->id)
        {
	        bzero(&msg, sizeof(t_msg));
	        msg.mtype = player->id + 1;
	        sprintf(msg.str, "Decremente next %d", player->id + 1);
	        msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
        }
        else
        {
          core->addr->players--;
          semOperation(core, -1);
        }
	      player->id--;
	    }
      if (semctl(core->semId, 0, GETVAL) == player->id)
	    {
	      /* printf("ITS MY TURN BITCHES\n"); */
	      if (checkAround(core, *player, 1) > 1)
	      {
	        i_die_msg(core, player);
	        return;
	      }
	      else
	       move(core, player);
	      if (player->id != 1 && semctl(core->semId, 0, GETVAL) == core->addr->players)
	       semOperation(core, -core->addr->players + 1);
	      else if (player->id == 1 && core->addr->players == 1)
	       exit(0);
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
  srand(time(NULL));
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  return (0);
}
