/*
** init_players.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Mar 28 13:20:24 2017 sellet_f
** Last update	Fri Mar 31 15:27:56 2017 gastal_r
*/

#include "lemipc.h"

void		initNewPlayer(t_struct *core, t_player *player, int idTeam)
{
  int		i;

  player->team = idTeam;
  player->id = core->addr->players + 1;
  player->x = rand() % (50 - 1);
  player->y = rand() % (50 - 1);
  i = player->y * 50 + player->x;
  while (core->addr->map[i] && core->addr->map[i] != EMPTY)
    {
      player->x = rand() % (50 - 1);
      player->y = rand() % (50 - 1);
      i = player->y * 50 + player->x;
    }
  if (checkNewTeam(core, idTeam) == 1)
    core->addr->teams += 1;
  core->addr->map[i] = idTeam;
  core->addr->players += 1;
}

int		initFirstPlayer(t_struct *core, int idTeam)
{
  t_player	player;

  if ((core->addr = (t_shared *) shmat(core->shmId, NULL,
				       SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  initMap(core);
  initNewPlayer(core, &player, idTeam);
  core->addr->players = 1;
  core->addr->teams = 1;
  firstPlayerLoop(core, &player);
  while (core->addr->teams > 1)
    timeDislayMap(core);
  system("clear");
  displayMap(core->addr->map);
  freeIPCS(core);
  return (0);
}

int		initOtherPlayers(t_struct *core)
{
  if ((core->addr = (t_shared *) shmat(core->shmId, NULL, SHM_R | SHM_W))
      == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  return (0);
}
