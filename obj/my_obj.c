/*
** test.c for salut in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Tue Feb 21 09:56:59 2017 Erwan Simon
** Last update Wed Mar  1 15:02:02 2017 Simon
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

int	filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

int	is_printable(char c)
{
  if (c >= 32 && c < 127)
    return (1);
  return (0);
}

void	print_head(char *name, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr)
{
  int	a;
  
  a = get_flags(shdr, ehdr);
  printf("\n%s:     file format elf64-x86-64\n", name);
  printf("architecture: i386:x86-64, flags 0x%08x:\n", a);
  print_flags(a, shdr, ehdr);
  printf("start address 0x%016x\n\n", (int) ehdr->e_entry);
}

void		proceed(char **av, int a)
{
  void		*data;
  Elf64_Ehdr	*elf;
  Elf64_Ehdr	*test;
  Elf64_Shdr	*shdr;
  int		fd;
  char		*strtab;

  if ((fd = open((av != NULL ? av[a] : "a.out"), O_RDONLY)) == -1)
    return ;
  if ((data = mmap(NULL, filesize(fd), PROT_READ,
		   MAP_SHARED, fd, 0)) == MAP_FAILED)
    return ;
  test = data;
  if (test->e_ident[0] == 127 && test->e_ident[1] == 'E'
      && test->e_ident[2] == 'L' && test->e_ident[3] == 'F')
    {
      elf = (Elf64_Ehdr *) data;
      shdr = (Elf64_Shdr *) (data + elf->e_shoff);
      strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
      print_head((av != NULL ? av[a] : "a.out"), shdr, elf);
      get_all(elf, shdr, strtab, data);
    }
  if (munmap(data, filesize(fd)) == -1)
    return ;
  close(fd);
}

int	main(int ac, char **av)
{
  int	a;

  a = 1;
  if (ac > 1)
    {
      while (a - 1 != ac)
	{
	  proceed(av, a);
	  a++;
	}
      return (0);
    }
  proceed(NULL, 0);
}
