##
## Makefile for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
##
## Made by Marin Alcaraz
## Login   <alcara_m@epitech.net>
##
## Started on  Fri Mar 01 09:38:17 2013 Marin Alcaraz
## Last update Wed Mar 20 17:28:25 2013 Marin Alcaraz
##

NAME	=	philo

SRC		=	philosophers.c \
			init_utils.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -lpthread

CC		=	cc

RM		=	rm -f
ECHO	=	echo -e

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@$(ECHO) '\033[0;33m> Compiled\033[0m'

clean	:
	$(RM) $(OBJ)
	@$(ECHO) '\033[0;33m> Directory cleaned\033[0m'

fclean	: clean
	$(RM) $(NAME)
	@$(ECHO) '\033[0;33m> Remove executable\033[0m'

re	: fclean all
