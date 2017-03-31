/*
** move.c for PSU_2016_lemipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 30 22:58:09 2017 gastal_r
** Last update	Fri Mar 31 00:57:56 2017 gastal_r
*/

#include      "lemipc.h"

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
	  i = y * MAP_SIZE + x;
	  if (y >= 0 && x >= 0 && i < MAP_SIZE * MAP_SIZE && core->addr->map[i] != EMPTY &&
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
  core->addr->map[player->y * MAP_SIZE + player->x] = 0;
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
  core->addr->map[player->y * MAP_SIZE + player->x] = player->team;
}

void  move(t_struct *core, t_player *player)
{
  t_player pos;
  int enemies;
  int allies;

  enemies = findClosestEnemy(core, player, &pos);
  allies = checkAroundAllies(core, *player, 3);
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
