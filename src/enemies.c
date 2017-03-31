/*
** enemies.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Mar 30 01:33:01 2017 sellet_f
** Last update	Thu Mar 30 21:58:07 2017 gastal_r
*/

#include "lemipc.h"

int		countEnemies(t_struct *core, t_player pos, int inRange)
{
  int		i;
  int		x;
  int		y;
  int		nbEnem;

  nbEnem = 0;
  y = pos.y - inRange - 1;
  while (++y <= pos.y + inRange)
    {
      x = pos.x - inRange - 1;
      while (++x <= pos.x + inRange)
	{
	  i = y * 50 + x;
	  if (y >= 0 && x >= 0 && i < 2500 && core->addr->map[i] != EMPTY &&
	      core->addr->map[i] == pos.team)
            nbEnem++;
        }
    }
  return (nbEnem);
}

int		getEnemyPosition(t_struct *core, t_player player,
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
	  i = y * 50 + x;
	  if (y >= 0 && x >= 0 && i < 2500 &&
	      core->addr->map[i] != EMPTY &&
	      core->addr->map[i] != player.team)
	    {
	      (pos != NULL ? pos->x = i % 50 : 0);
	      (pos != NULL ? pos->y = i / 50 : 0);
	      (pos != NULL ? pos->team = core->addr->map[i] : 0);
	      return (1);
	    }
	}
    }
  return (0);
}

int       findClosestEnemy(t_struct *core, t_player *player,
			   t_player *pos)
{
  int     nb;
  int     i;
  int     rt;

  i = 0;
  while ((rt = getEnemyPosition(core, *player, pos, i)) == 0 && i < 50)
    i++;
  if (rt == 0)
    return (0);
  nb = countEnemies(core, *pos, 3);
  return (nb);
}
