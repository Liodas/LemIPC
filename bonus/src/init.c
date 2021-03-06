/*
** init.c for Project-Master in /home/sellet_f/Projets/Tek2/PSU_2016_lemipc
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Mar 28 13:02:38 2017 sellet_f
** Last update	Sat Apr 01 10:33:03 2017 gastal_r
*/

#include "lemipc.h"

int		initSem(t_struct *core)
{
  if ((core->semId = semget(core->key, 1, SHM_R | SHM_W)) == -1)
    {
      if ((core->semId = semget(core->key, 1, IPC_CREAT | SHM_R | SHM_W))
          == -1)
	return (fprintf(stderr, "Semget failed\n") - 15);
      semctl(core->semId, 0, SETVAL, 1);
    }
  return (0);
}

int		initMsg(t_struct *core)
{
  if ((core->msgId = msgget(core->key, SHM_R | SHM_W)) == -1)
    {
      if ((core->msgId = msgget(core->key, IPC_CREAT | SHM_R | SHM_W)) == -1)
	return (fprintf(stderr, "Msgget failed\n") - 15);
    }
  return (0);
}

int		initValues(t_struct *core, char *path, int idTeam)
{
  t_player	player;

  if ((core->key = ftok(path, 0)) == -1)
    return (printUsage());
  initMsg(core);
  if (initSem(core) == -1)
    return (-1);
  if ((core->shmId =
       shmget(core->key, sizeof(t_shared)
	      + MAP_SIZE * MAP_SIZE * sizeof(int), SHM_R | SHM_W)) == -1)
    {
      if ((core->shmId = shmget(core->key, sizeof(t_shared)
				+ MAP_SIZE * MAP_SIZE * sizeof(int),
				IPC_CREAT | SHM_R | SHM_W)) != -1)
	if (initFirstPlayer(core, idTeam) == -1)
	  return (-1);
    }
  else
    {
      if (initOtherPlayers(core) == -1)
	return (-1);
      initNewPlayer(core, &player, idTeam);
      playerLoop(core, &player);
    }
  return (0);
}
