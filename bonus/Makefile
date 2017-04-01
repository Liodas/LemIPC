##
## Makefile for PSU_2016_lempipc
##
## Made by	gastal_r
## Login	gastal_r
##
## Started on	Sun Mar 26 12:28:17 2017 gastal_r
## Last update	Sun Mar 26 12:28:18 2017 gastal_r
##


CC		=       gcc

RM		=       rm -rf

CFLAGS		+=	-Wall -Wextra -W -Werror
CFLAGS		+=	-I./includes
CFLAGS	        +=      -lcsfml-{graphics,window,system}


NAME		=	lemipc

SRCS		=	src/main.c		\
			src/init.c		\
			src/allies.c		\
			src/enemies.c		\
			src/init_players.c	\
			src/player_loop.c	\
			src/move.c		\
			src/aff_func.c		\
			src/signal.c			\
			src/tryMoveDirections.c

OBJS		=	$(SRCS:.c=.o)

all		:       $(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean		:
			$(RM) $(OBJS)

fclean		:       clean
			$(RM) $(NAME)

re		:       fclean all

.PHONNY		:       all clean fclean re
