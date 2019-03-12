/*
** nm.h for nm in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Wed Feb 22 16:28:34 2017 Erwan Simon
** Last update Sun Feb 26 15:13:52 2017 Erwan Simon
*/

#ifndef NM_H_
# define NM_H_

#include <elf.h>

typedef struct	s_table {
  unsigned char	range;
  unsigned char	info;
  uint32_t	type;
  uint64_t	flags;
  char		letter;
}		t_table;

typedef struct	s_sort {
  unsigned int	value;
  int		info;
  char		type;
  char		*name;
  struct s_sort	*before;
  struct s_sort	*after;
}		t_sort;

char		get_letter(Elf64_Sym *, Elf64_Shdr *);
void		print(t_sort *);
t_sort		*add_node(t_sort *, int, Elf64_Addr, char, char *);
void		delete(t_sort *);

#endif /* !NM_H_ */
