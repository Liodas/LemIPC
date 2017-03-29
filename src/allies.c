/*
** allies.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Thu Mar 30 01:33:49 2017 sellet_f
** Last update Thu Mar 30 01:34:31 2017 chalie_a
*/

#include "lemipc.h"

int     findClosestAllies(t_struct *core, t_player *player, t_player *pos)
{
  (void) core;
  (void) player;
  (void) pos;
  return (0);
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
	  i = y * 50 + x;
	  if (y >= 0 && x >= 0 && i < 2500 &&
	      core->addr->map[i] != EMPTY &&
	      core->addr->map[i] == player.team)
	    allies++;
	}
    }
  return (allies);
}

