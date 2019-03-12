##
## Makefile for nm in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
## 
## Made by Erwan Simon
## Login   <erwan.simon@epitech.net>
## 
## Started on  Thu Feb 23 14:49:05 2017 Erwan Simon
## Last update Sun Feb 26 17:28:40 2017 Erwan Simon
##

NAME1	= my_nm
NAME2	= my_objdump

CC	= gcc

RM	= rm -f

SRCS1	= ./nm/table.c \
          ./nm/sort.c \
          ./nm/my_nm.c

SRCS2	= ./obj/get_infos.c \
	  ./obj/print_flags.c \
	  ./obj/my_obj.c

OBJS1	= $(SRCS1:.c=.o)

OBJS2	= $(SRCS2:.c=.o)

CFLAGS	= -I./nm/
CFLAGS	+= -W -Wall -Wextra

all: $(NAME1) $(NAME2)

nm: $(NAME1)

objdump: $(NAME2)

$(NAME1): $(OBJS1)
	$(CC) $(OBJS1) -o $(NAME1)

$(NAME2): $(OBJS2)
	$(CC) $(OBJS2) -o $(NAME2)

clean:
	$(RM) $(OBJS1) $(OBJS2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
