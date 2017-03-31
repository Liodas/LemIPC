/*
** player_loop.c for PSU_2016_lemipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 30 22:55:09 2017 gastal_r
** Last update	Fri Mar 31 19:20:52 2017 gastal_r
*/

#include    "lemipc.h"

int   waitNewTeam(t_struct *core, t_player *player)
{
  static int check = 0;
  int i;

  if (check == 0)
  {
    i = -1;
    while (++i < 50 * 50)
    {
      if (core->addr->map[i] != 0 && core->addr->map[i] != player->team)
        {
          check = 1;
          return (0);
        }
    }
  }
  return (1);
}

void  i_die_msg(t_struct *core, t_player *player)
{
  t_msg msg;

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
  core->addr->map[player->y * MAP_SIZE + player->x] = 0;
}

void   checkMessage(t_struct *core, t_player *player)
{
  t_msg msg;

  bzero(&msg, sizeof(t_msg));
  msgrcv(core->msgId, &msg, sizeof(t_msg), player->id, IPC_NOWAIT);
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
}

void  playerLoop(t_struct *core, t_player *player)
{
  while (core->addr->teams > 1)
    {
      usleep(1000);
      checkMessage(core, player);
      if (semctl(core->semId, 0, GETVAL) == player->id)
	    {
        player->id == 1 ? usleep(SPEED * 10) : 0;
	      if (checkAround(core, *player, 1) > 1)
	      {
	        i_die_msg(core, player);
          (checkNewTeam(core, player->team) == 1 ? core->addr->teams-- : 0);
	        return;
	      }
	      else
	       move(core, player);
	      if (player->id != 1
          && semctl(core->semId, 0, GETVAL) == core->addr->players)
	       semOperation(core, -core->addr->players + 1);
	      else if (player->id == 1 && core->addr->players == 1)
	       exit(0);
	      else
	       semOperation(core, 1);
	    }
    }
}

void		firstPlayerLoop(t_struct *core, t_player *player, t_graph *graph)
{
  int go_on;

  go_on = 1;
  while (go_on)
  {
    if (!checkPressedKey(graph))
      return;;
    usleep(SPEED);
     if (semctl(core->semId, 0, GETVAL) == 1)
    {
      if (checkAround(core, *player, 1) > 1)
        {
          i_die_msg(core, player);
          (checkNewTeam(core, player->team) == 1 ? core->addr->teams-- : 0);
          go_on = 0;
        }
      else
	    {
	      semOperation(core, 1);
	      move(core, player);
	    }
    }
    timeDislayMap(core, graph);
  }
}
