/*
** sort.c for nm in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Thu Feb 23 10:35:40 2017 Erwan Simon
** Last update Sun Feb 26 15:28:17 2017 Erwan Simon
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nm.h"

t_sort		*add_node(t_sort *first, int info,
			  Elf64_Addr value, char type, char *name)
{
  t_sort	*new;
  t_sort	*scroll;

  if ((new = malloc(sizeof(t_sort))) == NULL)
    exit(1);
  new->before = NULL;
  new->after = NULL;
  new->value = value;
  new->info = info;
  new->type = type;
  new->name = name;
  if ((scroll = first) == NULL)
    return (new);
  while (1)
    {
      if (strcmp(scroll->name, new->name) >= 0 && scroll->before != NULL)
	scroll = scroll->before;
      else if (strcmp(scroll->name, new->name) < 0 && scroll->after != NULL)
	scroll = scroll->after;
      else
	break ;
    }
  strcmp(scroll->name, new->name) >= 0 ?
    (scroll->before = new) : (scroll->after = new);
  return (NULL);
}

void	print(t_sort *current)
{
  if (current == NULL)
    return ;
  if (current->before != NULL)
    print(current->before);
  if (current->type != 'U' && current->type != 'w' && current->info != 4)
    printf("%016x %c %s\n", (unsigned int)
	   current->value, current->type, current->name);
    else
    printf("                 %c %s\n",
	   current->type, current->name);
  if (current->after != NULL)
    print(current->after);
}

void	delete(t_sort *current)
{
  if (current == NULL)
    return ;
  if (current->before != NULL)
    delete(current->before);
  if (current->after != NULL)
    delete(current->after);
  free(current);
}
