/*
** init_players.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Mar 28 13:20:24 2017 sellet_f
** Last update	Thu Mar 30 19:42:48 2017 gastal_r
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
  while (core->addr->map[i] != EMPTY)
    {
      player->x = rand() % (50 - 1);
      player->y = rand() % (50 - 1);
      i = player->y * 50 + player->x;
    }
  core->addr->map[i] = idTeam;
  core->addr->players += 1;
  checkNewTeam(core, idTeam);
}

void		mainloopFirstPlayer(t_struct *core, t_player *player)
{
  clock_t t1 = clock();
  clock_t t2;
  int go_on;

  go_on = 1;
  while (go_on)
  {
    if (semctl(core->semId, 0, GETVAL) == 1)
    {
      if (checkAround(core, *player, 1) > 1)
        {
          i_die_msg(core, player);
          go_on = 0;
        }
      else
	    {
	      semOperation(core, 1);
	      (core->addr->players > 1 ? move(core, player) : (void)0);
	    }
  //displayMap(core->addr->map);
    }
    t2 = clock();
    if (t2 - t1 >= 10000)
    {
      //system("clear");
      printf("\033[2J\033[1;1H");
      displayMap(core->addr->map);
      t1 = clock();
    }
  }
}

void		freeIPCS(t_struct *core)
{

}

int		initFirstPlayer(t_struct *core, int idTeam)
{
  t_player	player;
  clock_t t1 = clock();
  clock_t t2;

  /* printf("shmid %d\n", core->shmId); */
  if ((core->addr = (t_shared *) shmat(core->shmId, NULL,
				       SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  /* printf("%p\n", core->addr); */
  initMap(core);
  initNewPlayer(core, &player, idTeam);
  core->addr->players = 1;
  core->addr->teams = 1;
  mainloopFirstPlayer(core, &player);
  while (1) // check team on map
  {
    t2 = clock();
    if (t2 - t1 >= 10000)
    {
      //system("clear");
      printf("\033[2J\033[1;1H");
      displayMap(core->addr->map);
      t1 = clock();
    }
  }
  freeIPCS(core);
return (0);
}

int		initOtherPlayers(t_struct *core)
{
  /* printf("%p\n", core->addr); */
  /* printf("shmid %d\n", core->shmId); */
  if ((core->addr = (t_shared *) shmat(core->shmId, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  /* printf("%p\n", core->addr); */
  return (0);
}
