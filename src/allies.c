/*
** allies.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Mar 30 01:33:49 2017 sellet_f
** Last update	Thu Mar 30 17:36:53 2017 gastal_r
*/

#include "lemipc.h"

int		countAllies(t_struct *core, t_player pos, int inRange)
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
      /* printf("\n"); */
    }
  return (nbEnem);
}

int       getAlliesPosition(t_struct *core, t_player player,
			   t_player *pos, int inRange)
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
	  if (y >= 0 && x >= 0 && i < 2500
      && core->addr->map[i] != EMPTY
      && core->addr->map[i] == player.team
      && i != player.y * 50 + player.x)
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

int     findClosestAllies(t_struct *core, t_player *player, t_player *pos)
{
  int     nb;
  int     i;
  int     rt;

  i = 0;
  while ((rt = getAlliesPosition(core, *player, pos, i)) == 0 && i < 50)
    i++;
  if (rt == 0)
    return (0);
  //printf("ALLIES RANGE%d posx=%d  posy=%d team=%d\n", i, pos->x, pos->y, pos->team);

  nb = countAllies(core, *pos, 3);
  //printf("allies=%d\n", nb);
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
	  i = y * 50 + x;
	  if (y >= 0 && x >= 0 && i < 2500 &&
	      core->addr->map[i] != EMPTY &&
	      core->addr->map[i] == player.team)
	    allies++;
	}
    }
  return (allies);
}
