/*
** lemipc.h for PSU_2016_lempipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 12:30:19 2017 gastal_r
** Last update	Fri Mar 31 02:20:44 2017 gastal_r
*/

#ifndef     __LEMIPC_H__
# define    __LEMIPC_H__

# include   <sys/types.h>
# include   <sys/ipc.h>
# include   <sys/sem.h>
# include   <sys/shm.h>
# include   <sys/msg.h>
# include   <stdio.h>
# include   <string.h>
# include   <stdlib.h>
# include   <unistd.h>
# include   <time.h>

# define    EMPTY 0
# define    SPEED 5000

typedef struct			s_msg
{
  long				mtype;
  char				str[32];
}				t_msg;

typedef struct			s_player
{
  int				x;
  int				y;
  int				team;
  int				id;
}				t_player;

typedef struct			s_shared
{
  int				players;
  int				teams;
  int				map[0];
}  __attribute__((packed))	t_shared;

typedef struct			s_struct
{
  key_t				key;
  int				semId;
  int				shmId;
  int				msgId;
  t_shared			*addr;
}				t_struct;

int	getEnemyPosition(t_struct *, t_player, t_player *, int);
int	findClosestAllies(t_struct *, t_player *, t_player *);
int	findClosestEnemy(t_struct *, t_player *, t_player *);
int	checkAroundAllies(t_struct *, t_player, int);
void	initNewPlayer(t_struct *, t_player *, int);
void	tryMoveRight(t_struct *, t_player *, int);
void	tryMoveLeft(t_struct *, t_player *, int);
void	tryMoveDown(t_struct *, t_player *, int);
int	countEnemies(t_struct *, t_player, int);
void	firstPlayerLoop(t_struct *, t_player *);
int	checkAround(t_struct *, t_player, int);
void	tryMoveUp(t_struct *, t_player *, int);
int	initValues(t_struct *, char *, int);
void	playerLoop(t_struct *, t_player *);
void	playerLoop(t_struct *, t_player *);
void	i_die_msg(t_struct *, t_player *);
int	initFirstPlayer(t_struct *, int);
void	semOperation(t_struct *, int );
int	checkNewTeam(t_struct *, int);
int	initOtherPlayers(t_struct *);
void	move(t_struct *, t_player *);
void    timeDislayMap(t_struct *);
void	freeIPCS(t_struct *);
int	initMsg(t_struct *);
int	initSem(t_struct *);
void	initMap(t_struct *);
void	displayMap(int *);
int	printUsage();

#endif
