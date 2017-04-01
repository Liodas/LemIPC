/*
** aff_func.c for PSU_2016_lemipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 30 23:04:16 2017 gastal_r
** Last update	Sat Apr 01 12:14:06 2017 gastal_r
*/

#include    "lemipc.h"

int		printUsage(void)
{
  printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key \
is a valid path that will be used by ftok\nteam_number is the team number \
assigned to the current player\n");
  return (-1);
}

void    setTeamColor(sfRectangleShape *rect, int nb)
{
  sfColor color;

  (nb == 0 ? color = sfRed :
   nb == 1 ? color = sfGreen :
    nb == 2 ? color = sfBlue :
     nb == 3 ? color = sfYellow :
      nb == 4 ? color = sfMagenta :
       nb == 5 ? color = sfCyan :
        (color = sfWhite));
  sfRectangleShape_setFillColor(rect, color);
}

void    drawSquare(int x, int y, t_graph *graph, int nb)
{
  sfVector2f pos;
  sfVector2f size;

  pos.x = x * 3;
  pos.y = y * 3;
  size.x = 3;
  size.y = 3;
  sfRectangleShape_setSize(graph->rect, size);
  setTeamColor(graph->rect, nb);
  sfRectangleShape_setPosition(graph->rect, pos);
  sfRenderWindow_drawRectangleShape(graph->win, graph->rect, NULL);
}

void		displayMap(int *map, t_graph *graph)
{
  int		x;
  int		y;
  int		i;

  sfRenderWindow_clear(graph->win, sfBlack);
  x = -1;
  while (++x < MAP_SIZE + 1)
    drawSquare(x, 0, graph, 10);
  x = -1;
  while (++x < MAP_SIZE)
    {
      y = -1;
      while (++y < MAP_SIZE)
	{
    drawSquare(0, y, graph, 10);
	  i = y * MAP_SIZE + x;
	  map[i] != 0 ? drawSquare(x + 1, y + 1, graph, map[i]) : (void)0;
	}
    drawSquare(y, x + 1, graph, 10);
    }
   x = -1;
   while (++x <= MAP_SIZE)
    drawSquare(x, y, graph, 10);
   sfRenderWindow_display(graph->win);
}

void    timeDislayMap(t_struct *core, t_graph *graph)
{
  static clock_t t1 = SPEED;
  clock_t t2;

  t2 = clock();
  if (t2 - t1 >= SPEED)
  {
    displayMap(core->addr->map, graph);
    t1 = clock();
  }
}
