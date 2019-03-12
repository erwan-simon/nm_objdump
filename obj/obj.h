/*
** nm.h for nm in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Wed Feb 22 16:28:34 2017 Erwan Simon
** Last update Sun Feb 26 17:37:05 2017 Erwan Simon
*/

#ifndef NM_H_
# define NM_H_

#include <elf.h>

int	is_printable(char);
void	get_all(Elf64_Ehdr *, Elf64_Shdr *, char *, char *);
int	get_flags(Elf64_Shdr *, Elf64_Ehdr *);
void	print_flags(int, Elf64_Shdr *, Elf64_Ehdr *);

#endif /* NM_H_ */
