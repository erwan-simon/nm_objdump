/*
** print_flags.c for obj in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump/obj
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Sun Feb 26 17:00:27 2017 Erwan Simon
** Last update Sun Feb 26 18:18:56 2017 Erwan Simon
*/

#include <stdio.h>
#include <elf.h>
#include "flags.h"
#include "obj.h"

void	print_flags(int a, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr)
{
  int	i;

  i = 0;
  if (ehdr->e_type == ET_EXEC)
    printf("EXEC_P");
  else if (ehdr->e_type == ET_DYN)
    printf("DYNAMIC");
  while (i < ehdr->e_shnum)
    {
      if ((shdr[i].sh_type == SHT_RELA || shdr[i].sh_type == SHT_REL)
	  && a % 10 == 1)
	printf("HAS_RELOC");
      if (shdr[i].sh_type == SHT_SYMTAB)
	printf("%sHAS_SYMS", (a % 10 == 0 ? "" : ", "));
      if (shdr[i].sh_type == SHT_HASH)
	printf("%sD_PAGED", (a - 100 == 0 ? "" : ", "));
      i++;
    }
  if (a != 0)
    printf("\n");
}
