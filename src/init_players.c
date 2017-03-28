/*
** init_players.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Tue Mar 28 13:20:24 2017 sellet_f
** Last update Tue Mar 28 15:35:12 2017 chalie_a
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
  t_msg		msg;

  printf("shmid %d\n", core->shmId);
  if ((core->addr = shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  printf("%p\n", core->addr);
  if (initSem(core) == -1)
    return (-1);
  initMap(core);
  initNewPlayer(core, &player, idTeam);
  displayMap(core->addr->map);
  core->addr->players = 1;
  core->addr->teams = 1;
  while (go_on)
    {
      sleep(1);
      printf("players= %d  teams=%d\n", core->addr->players, core->addr->teams);
      bzero(&msg, sizeof(t_msg));
      printf("Created msg %d\n", core->msgId);
      msgrcv(core->msgId, &msg, sizeof(t_msg), 666, IPC_NOWAIT);
      printf("%s\n", msg.str);
      
      // check msg
      // check mort
      // check poto
      // move
    }
  return (0);
}

int		initOtherPlayers(t_struct *core)
{
  //core->addr->teams += 1;
  printf("%p\n", core->addr);
  printf("shmid %d\n", core->shmId);
  if ((core->addr = shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  printf("%p\n", core->addr);
  displayMap(core->addr->map);
  return (0);
}
