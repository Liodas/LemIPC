/*
** signal.c for PSU_2016_lemipc
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Apr 01 22:44:57 2017 gastal_r
** Last update	Sat Apr 01 22:44:58 2017 gastal_r
*/

#include "lemipc.h"

int sig_check = 0;

void	signalHandler(int type)
{
  (void) type;
  sig_check = 1;
}
