/*
** proceed.c for obj in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump/obj
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Sat Feb 25 17:26:25 2017 Erwan Simon
** Last update Wed Mar  1 15:01:43 2017 Simon
*/

#include <elf.h>
//#include <libelf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "flags.h"
#include "obj.h"

int	get_flags(Elf64_Shdr *shdr, Elf64_Ehdr *ehdr)
{
  int	a;
  int	i;

  i = 0;
  a = 0;
  if (ehdr->e_type == ET_EXEC)
    a += EXEC_P;
  else if (ehdr->e_type == ET_DYN)
    a += DYNAMIC;
  while (i < ehdr->e_shnum)
    {
      if ((shdr[i].sh_type == SHT_RELA || shdr[i].sh_type == SHT_REL) && a == 0)
	a += HAS_RELOC;
      if (shdr[i].sh_type == SHT_SYMTAB)
	a += HAS_SYMS;
      if (shdr[i].sh_type == SHT_HASH)
	a += D_PAGED;
      i++;
    }
  return (a);
}

void	get_hexa(Elf64_Shdr *shdr, char *data, unsigned int idx)
{
  int	a;

  a = 0;
  while (a < 16 && idx + a < shdr->sh_size)
    {
      if (a % 4 == 0)
	printf(" ");
      printf("%02x", (unsigned char)
	     *(data + shdr->sh_offset + idx + a));
      a++;
    }
  while (a < 16)
    {
      if (a % 4 == 0)
	printf(" ");
      printf("  ");
      a++;
    }
}

void	get_char(Elf64_Shdr *shdr, char *data, unsigned int idx)
{
  int	a;

  a = 0;
  while (a < 16 && idx + a < shdr->sh_size)
    {
      printf("%c",
	     is_printable(*(data + shdr->sh_offset + idx + a))
	     ? *(data + shdr->sh_offset + idx + a)  : '.');
      a++;
    }
  while (a < 16)
    {
      printf(" ");
      a++;
    }
}

void		get_addr(Elf64_Shdr *shdr, char *data)
{
  unsigned int	addr;
  unsigned int	idx;

  addr = shdr->sh_addr;
  idx = 0;
  while (idx < shdr->sh_size)
    {
      printf(" %04x", addr);
      addr += 16;
      get_hexa(shdr, data, idx);
      printf("  ");
      get_char(shdr, data, idx);
      idx += 16;
      printf("\n");
    }
}

void	get_all(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *strtab, char *data)
{
  int	i;

  i = 0;
  while (i < ehdr->e_shnum)
    {
      if (strcmp(strtab + shdr[i].sh_name, "") != 0
	  && strcmp(strtab + shdr[i].sh_name, ".bss") != 0
	  && strcmp(strtab + shdr[i].sh_name, ".shstrtab") != 0
	  && strcmp(strtab + shdr[i].sh_name, ".symtab") != 0
	  && strcmp(strtab + shdr[i].sh_name, ".strtab") != 0)
	{
	  printf("Contents of section %s:\n",
		 strtab + shdr[i].sh_name);
	  get_addr(&shdr[i], data);
	}
      i++;
    }
}
