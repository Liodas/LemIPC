/*
** tryMoveDirections.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Thu Mar 30 01:21:56 2017 sellet_f
** Last update Thu Mar 30 01:23:47 2017 chalie_a
*/

#include "lemipc.h"

int	checkNextMove(t_struct *core, int x, int y)
{
  if (y > 0 && x > 0 && core->addr->map[y * 50 + x] == 0)
    return (1);
  return (0);
}

int	tryMoveLeft(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x - 1, player->y) == 0)
    if (dir == 0)
      {
	if (checkNextMove(core, player->x, player->y - 1) != 0)
	  player->y--;
	else if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else if (checkNextMove(core, player->x + 1, player->y) != 0)
	  player->x++;
	else
	  return (0);
      }
    else
      {
	if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else if (checkNextMove(core, player->x, player->y - 1) != 0)
	  player->y--;
	else if (checkNextMove(core, player->x + 1, player->y) != 0)
	  player->x++;
	else
	  return (0);
      }
  else
    player->x--;
  return (1);
}

int	tryMoveRight(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x + 1, player->y) == 0)
    if (dir == 0)
      {
	if (checkNextMove(core, player->x, player->y - 1) != 0)
	  player->y--;
	else if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else if (checkNextMove(core, player->x - 1, player->y) != 0)
	  player->x--;
	else
	  return (0);
      }
    else
      {
	if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else if (checkNextMove(core, player->x, player->y - 1) != 0)
	  player->y--;
	else if (checkNextMove(core, player->x - 1, player->y) != 0)
	  player->x--;
	else
	  return (0);
      }
  else
    player->x++;
  return (1);
}

int	tryMoveUp(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x, player->y + 1) == 0)
      if (dir == 0)
	{
	  if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else
	    return (0);
	}
      else
	{
	  if (checkNextMove(core, player->x + 1, player->y) != 0)
	    player->x++;
	  else if (checkNextMove(core, player->x - 1, player->y) != 0)
	    player->x--;
	  else if (checkNextMove(core, player->x, player->y - 1) != 0)
	    player->y--;
	  else
	    return (0);
	}
  else
    player->y++;
  return (1);
}

int	tryMoveDown(t_struct *core, t_player *player, int dir)
{
  if (checkNextMove(core, player->x, player->y - 1) == 0)
    if (dir == 0)
      {
	if (checkNextMove(core, player->x + 1, player->y) != 0)
	  player->x++;
	else if (checkNextMove(core, player->x - 1, player->y) != 0)
	  player->x--;
	else if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else
	  return (0);
      }
    else
      {
	if (checkNextMove(core, player->x - 1, player->y) != 0)
	  player->x--;
	else if (checkNextMove(core, player->x + 1, player->y) != 0)
	  player->x++;
	else if (checkNextMove(core, player->x, player->y + 1) != 0)
	  player->y++;
	else
	  return (0);
      }
  else
    player->y--;
  return (1);
}
