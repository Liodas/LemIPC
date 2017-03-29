/*
** init_players.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Mar 28 13:20:24 2017 sellet_f
** Last update	Wed Mar 29 13:20:26 2017 gastal_r
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
  printf("I ++++++++ %d\n", i);
  while (core->addr->map[i] != EMPTY)
    {
      player->x = rand() % (50 - 1);
      player->y = rand() % (50 - 1);
      i = player->y * 50 + player->x;
      printf("I ++++++++ %d\n", i);
    }
  core->addr->map[i] = idTeam;
  core->addr->players += 1;
}

int		initFirstPlayer(t_struct *core, int go_on, int idTeam)
{
  t_player	player;

  printf("shmid %d\n", core->shmId);
  if ((core->addr = (t_shared *) shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  printf("%p\n", core->addr);
  initMap(core);
  initNewPlayer(core, &player, idTeam);
  displayMap(core->addr->map);
  core->addr->players = 1;
  core->addr->teams = 1;
  while (go_on)
  {
    sleep(1);
    printf("players= %d  teams=%d\n", core->addr->players, core->addr->teams);
    printf("sem=%d\n", semctl(core->semId, 0, GETVAL));
    if (semctl(core->semId, 0, GETVAL) == 1)
    {
      displayMap(core->addr->map);
      printf("ITS MY TURN BITCHES\n");
      if (checkAround(core, player, 0, 1) != 0)
        {
          i_die_msg(core, &player);
          go_on = 0;
        }
      else
      {
        semOperation(core, 1);
        (core->addr->players > 2 ? move(core, &player) : 0);
      }
    }
  }
  while (1) // check team on map
  {
    sleep(1);
    printf("players= %d  teams=%d\n", core->addr->players, core->addr->teams);
    printf("sem=%d\n", semctl(core->semId, 0, GETVAL));
    displayMap(core->addr->map);
  }
return (0);
}

int		initOtherPlayers(t_struct *core)
{
  printf("%p\n", core->addr);
  printf("shmid %d\n", core->shmId);
  if ((core->addr = (t_shared *) shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  printf("%p\n", core->addr);
  displayMap(core->addr->map);
  return (0);
}
