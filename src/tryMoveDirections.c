/*
** tryMoveDirections.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Mar 30 01:21:56 2017 sellet_f
** Last update	Thu Mar 30 22:37:09 2017 gastal_r
*/

#include "lemipc.h"

int	checkNextMove(t_struct *core, int x, int y)
{
  if (y > 0 && x > 0 && core->addr->map[y * 50 + x] == 0)
    return (1);
  return (0);
}

void	tryMoveLeft(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x - 1, player->y) == 0)
    {
      if (dir == 0)
	{
	  if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	  else if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	}
      else
	{
	  if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	}
    }
  else
    player->x--;
}

void	tryMoveRight(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x + 1, player->y) == 0)
    {
      if (dir == 0)
	{
	  if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	  else if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	}
      else
	{
	  if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	}
    }
  else
    player->x++;
}

void	tryMoveUp(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x, player->y + 1) == 0)
    {
      if (dir == 0)
	{
	  if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	}
      else
	{
	  if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	}
    }
  else
    player->y++;
}

void	tryMoveDown(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x, player->y - 1) == 0)
    {
      if (dir == 0)
	{
	  if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	}
      else
	{
	  if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x, player->y + 1) != 0)
	    player->y++;
	}
    }
  else
    player->y--;
}
