/*
** main.c for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:28:14 2017 gastal_r
** Last update	Wed Mar 29 15:32:41 2017 gastal_r
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
    map[i] != 0 ? printf("%d ", map[i]) : printf(" ");
	}
      printf("\n");
    }
}

//int

int		countEnemies(t_struct *core, t_player pos, int inRange)
{
  int		i;
  int		x;
  int		y;
  int   nbEnem;

  nbEnem = 0;
  y = pos.y - inRange - 1;
  while (++y <= pos.y + inRange)
    {
      x = pos.x - inRange - 1;
      while (++x <= pos.x + inRange)
	     {
	        i = y * 50 + x;
          //printf("%d", core->addr->map[i]);
	        if (y >= 0 && x >= 0 && i < 2500 && core->addr->map[i] != EMPTY &&
	          core->addr->map[i] == pos.team)
            nbEnem++;
        }
      printf("\n");
    }
  return (nbEnem);
}

int       getEnemyPosition(t_struct *core, t_player player, t_player *pos, int inRange)
{
  int		i;
  int		x;
  int		y;
  int nbEnem;

  nbEnem = 0;
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
          (pos != NULL ? pos->x = i % 50 : 0);
          (pos != NULL ? pos->y = i / 50 : 0);
          (pos != NULL ? pos->team = core->addr->map[i] : 0);
           nbEnem++;
        }
      }
  }
  return (nbEnem);
}

int       findClosestEnemy(t_struct *core, t_player *player, t_player *pos)
{
  int     nb;
  int     i;

  i = 0;
  while (getEnemyPosition(core, *player, pos, i) == 0 && i < 50)
    i++;
  printf("ENEMY RANGE%d posx=%d  posy=%d team=%d\n", i, pos->x, pos->y, pos->team);

  nb = countEnemies(core, *pos, 5);
  printf("enemy=%d\n", nb);
  return (nb);
}

int     findClosestAllies(t_struct *core, t_player *player, t_player *pos)
{
  (void) core;
  (void) player;
  (void) pos;
  return (0);
}

int		checkAroundAllies(t_struct *core, t_player player, int inRange)
{
  int		i;
  int		x;
  int		y;
  int allies;

  allies = 0;
  y = player.y - inRange - 1;
  while (++y <= player.y + inRange)
    {
      x = player.x - inRange - 1;
      while (++x <= player.x + inRange)
	     {
	        i = y * 50 + x;
	        if (y >= 0 && x >= 0 && i < 2500 && core->addr->map[i] != EMPTY &&
	           core->addr->map[i] == player.team)
	            allies++;
	      }
    }
  return (allies);
}

void  tryMove(t_struct *core, t_player *player, t_player pos)
{
  int dir;
  
  dir = rand() % 2;
  core->addr->map[player->y * 50 + player->x] = 0;
  if (pos.x > player->x && pos.y == player->y)
    (core->addr->map[player->y * 50 + player->x + 1] == 0 ? player->x++ :
     core->addr->map[player->y * 50 + player->x + 1] != 0 && dir == 0 ? player->y++ : player->y--);
  else if (pos.y > player->y && pos.x == player->x)
    (core->addr->map[(player->y + 1) * 50 + player->x] == 0 ? player->y++ :
     core->addr->map[(player->y + 1) * 50 + player->x] != 0 && dir == 0 ? player->x++ : player->x--);
  else if (pos.x < player->x && pos.y == player->y)
    (core->addr->map[player->y * 50 + player->x - 1] == 0 ? player->x-- :
     core->addr->map[player->y * 50 + player->x - 1] != 0 && dir == 0 ? player->y++ : player->y--);
  else if (pos.y < player->y && pos.x == player->x)
    (core->addr->map[(player->y - 1) * 50 + player->x] == 0 ? player->y-- :
     core->addr->map[(player->y - 1) * 50 + player->x] != 0 && dir == 0 ? player->x++ : player->x--);
  else if (pos.x > player->x && pos.y > player->y)
    (dir == 0 ? player->x++ : player->y++);
  else if (pos.x < player->x && pos.y > player->y)
    (dir == 0 ? player->x-- : player->y++);
  else if (pos.x > player->x && pos.y < player->y)
    (dir == 0 ? player->x++ : player->y--);
  else if (pos.x < player->x && pos.y < player->y)
    (dir == 0 ? player->x-- : player->y--);
  core->addr->map[player->y * 50 + player->x] = player->team;
}

void  move(t_struct *core, t_player *player)
{
  t_player pos;

  if (findClosestEnemy(core, player, &pos) <= checkAroundAllies(core, *player, 5))
    {
      tryMove(core, player, pos);
      printf("MOVE %d %d\n", pos.x, pos.y);
      // TODO go to x y
    }
  else
  {
    findClosestAllies(core, player, &pos);
    // TODO go to x y
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

  bzero(&msg, sizeof(t_msg));
  msg.mtype = player->id + 1;
  sprintf(msg.str, "%d Died", player->id);
  msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
  printf("message sended\n");
  core->addr->players--;
  core->addr->map[player->y * 50 + player->x] = 0;
}

void  mainloop(t_struct *core, t_player *player)
{
  t_msg msg;

  while (1)
  {
    usleep(10000);
    bzero(&msg, sizeof(t_msg));
    msgrcv(core->msgId, &msg, sizeof(t_msg), player->id, IPC_NOWAIT);
    /* printf("playerid=%d %s\n",player->id, msg.str); */
    /* printf("sem=%d\n", semctl(core->semId, 0, GETVAL)); */
    if (strlen(msg.str) > 0)
    {
      bzero(&msg, sizeof(t_msg));
      msg.mtype = player->id + 1;
      sprintf(msg.str, "Decremente next %d", player->id + 1);
      msgsnd(core->msgId, &msg, sizeof(t_msg), 0);
      player->id--;
    }
    if (semctl(core->semId, 0, GETVAL) == player->id)
    {
      printf("ITS MY TURN BITCHES\n");
      if (checkAround(core, *player, 1) > 1)
      {
        i_die_msg(core, player);
        return;
      }
      else
        move(core, player);
      if (player->id != 1 && semctl(core->semId, 0, GETVAL) == core->addr->players)
      {
        semOperation(core, -core->addr->players + 1);
      }
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
  if (initValues(&core, av[1], atoi(av[2])) == -1)
    return (-1);
  return (0);
}
