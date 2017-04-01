/*
** init_players.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Mar 28 13:20:24 2017 sellet_f
** Last update	Sat Apr 01 22:54:06 2017 gastal_r
*/

#include "lemipc.h"

extern int	sig_check;

void		initNewPlayer(t_struct *core, t_player *player, int idTeam)
{
  int		i;

  player->team = idTeam;
  player->id = core->addr->players + 1;
  player->x = rand() % (MAP_SIZE - 1);
  player->y = rand() % (MAP_SIZE - 1);
  i = player->y * MAP_SIZE + player->x;
  while (core->addr->map[i] && core->addr->map[i] != EMPTY)
    {
      player->x = rand() % (MAP_SIZE - 1);
      player->y = rand() % (MAP_SIZE - 1);
      i = player->y * MAP_SIZE + player->x;
    }
  if (checkNewTeam(core, idTeam) == 1)
    {
      core->addr->teams += 1;
      (core->addr->checkTeams == 1 ? core->addr->checkTeams = 0 : 0);
    }
  core->addr->map[i] = idTeam;
  core->addr->players += 1;
}

void		initGraph(t_graph *graph)
{
  sfVideoMode	mode;

  mode.width = WINDOW_SIZE;
  mode.height = WINDOW_SIZE;
  mode.bitsPerPixel = 32;
  graph->win = sfRenderWindow_create(mode, "LemIPC", sfResize | sfClose, NULL);
  sleep(1);
  graph->rect = sfRectangleShape_create();
}

void		freeGraph(t_graph *graph)
{
  sfRenderWindow_destroy(graph->win);
  sfRectangleShape_destroy(graph->rect);
}

int		initFirstPlayer(t_struct *core, int idTeam)
{
  t_player	player;
  t_graph	graph;

  if ((core->addr = (t_shared *) shmat(core->shmId, NULL,
				       SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Shmat failed\n") - 14);
  bzero(&core->addr->map, 50 * 50);
  initNewPlayer(core, &player, idTeam);
  core->addr->players = 1;
  core->addr->teams = 1;
  core->addr->checkTeams = 1;
  initGraph(&graph);
  signal(SIGINT, signalHandler);
  firstPlayerLoop(core, &player, &graph);
  while (sfRenderWindow_isOpen(graph.win))
    {
      checkEvent(core, &graph);
      timeDislayMap(core, &graph);
    }
  freeGraph(&graph);
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
