/*
** lemipc.h for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:30:19 2017 gastal_r
** Last update	Sun Mar 26 12:31:26 2017 gastal_r
*/

#ifndef __LEMIPC_H__
# define __LEMIPC_H__

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <stdio.h>

# define EMPTY 0

typedef struct	s_player
{
  int		x;
  int		y;
  int		team;
}		t_player;

typedef struct	s_struct
{
  key_t		key;
  int		semId;
  int		shmId;
  int		msgId;
  void		*addr;
}		t_struct;

#endif
