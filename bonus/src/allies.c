/*
** allies.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Mar 30 01:33:49 2017 sellet_f
** Last update	Fri Mar 31 12:50:08 2017 gastal_r
*/

#include "lemipc.h"

int		countAllies(t_struct *core, t_player pos, int inRange)
{
  int		i;
  int		x;
  int		y;
  int   nbAllies;

  nbAllies = 0;
  y = pos.y - inRange - 1;
  while (++y <= pos.y + inRange)
    {
      x = pos.x - inRange - 1;
      while (++x <= pos.x + inRange)
	{
	  i = y * MAP_SIZE + x;
	  if (y >= 0 && x >= 0 && i < MAP_SIZE * MAP_SIZE && core->addr->map[i] != EMPTY &&
	      core->addr->map[i] == pos.team)
            nbAllies++;
        }
    }
  return (nbAllies);
}

int       getAlliesPosition(t_struct *core, t_player player,
			   t_player *pos, int inRange)
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
	  i = y * MAP_SIZE + x;
	  if (y >= 0 && x >= 0 && i < MAP_SIZE * MAP_SIZE
      && core->addr->map[i] != EMPTY
      && core->addr->map[i] == player.team
      && i != player.y * MAP_SIZE + player.x)
	    {
	      (pos != NULL ? pos->x = i % MAP_SIZE : 0);
	      (pos != NULL ? pos->y = i / MAP_SIZE : 0);
	      (pos != NULL ? pos->team = core->addr->map[i] : 0);
	      return (1);
	    }
	}
    }
  return (0);
}

int     findClosestAllies(t_struct *core, t_player *player, t_player *pos)
{
  int     nb;
  int     i;
  int     rt;

  i = 0;
  while ((rt = getAlliesPosition(core, *player, pos, i)) == 0 && i < MAP_SIZE)
    i++;
  if (rt == 0)
    return (0);
  nb = countAllies(core, *pos, 5);
  return (nb);
}

int		checkAroundAllies(t_struct *core, t_player player,
				  int inRange)
{
  int		i;
  int		x;
  int		y;
  int		allies;

  allies = 0;
  y = player.y - inRange - 1;
  while (++y <= player.y + inRange)
    {
      x = player.x - inRange - 1;
      while (++x <= player.x + inRange)
	{
	  i = y * MAP_SIZE + x;
	  if (y >= 0 && x >= 0 && i < MAP_SIZE * MAP_SIZE &&
	      core->addr->map[i] != EMPTY &&
	      core->addr->map[i] == player.team)
	    allies++;
	}
    }
  return (allies);
}
