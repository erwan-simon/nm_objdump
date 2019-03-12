/*
** test.c for salut in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Tue Feb 21 09:56:59 2017 Erwan Simon
** Last update Wed Mar  1 15:34:35 2017 Simon
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
#include "nm.h"

int	filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

t_sort		*send(Elf64_Sym *sym, unsigned int size,
		      char *nametab, Elf64_Shdr *shdr)
{
  t_sort	*first;
  unsigned int	i;

  i = 0;
  first = NULL;
  while (i != size)
    {
      if (strcmp("", nametab + sym[i].st_name) != 0 &&
	  get_letter(&sym[i], shdr) != 'a')
	{
	  if (first == NULL)
	    first = add_node(NULL,  sym[i].st_info, sym[i].st_value,
			     get_letter(&sym[i], shdr),
			     nametab + sym[i].st_name);
	  else
	    add_node(first, sym[i].st_info, sym[i].st_value,
		     get_letter(&sym[i], shdr),
		     nametab + sym[i].st_name);
	}
      i++;
    }
  return (first);
}

void		get_all(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr,
			char *strtab, char *data)
{
  char		*nametab;
  Elf64_Sym	*sym;
  unsigned int	size;
  int		i;
  t_sort	*first;

  sym = NULL;
  nametab = NULL;
  i = 0;
  while (i < ehdr->e_shnum)
    {
      if (strcmp(strtab + shdr[i].sh_name, ".symtab") == 0)
	{
	  sym = (Elf64_Sym *) (data + (shdr + i)->sh_offset);
	  size = (shdr + i)->sh_size / sizeof(Elf64_Sym);
	}
      else if (strcmp(strtab + shdr[i].sh_name, ".strtab") == 0)
	nametab = (data + (shdr + i)->sh_offset);
      i++;
    }
  first = send(sym, size, nametab, shdr);
  print(first);
  delete(first);
}

void		proceed(int ac, char **av, int a)
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
    exit(84);
  test = data;
  if (test->e_ident[0] == 127 && test->e_ident[1] == 'E'
      && test->e_ident[2] == 'L' && test->e_ident[3] == 'F')
    {
      if (ac > 2)
	printf("\n%s:\n", (av != NULL ? av[a] : "a.out"));
      elf = (Elf64_Ehdr *) data;
      shdr = (Elf64_Shdr *) (data + elf->e_shoff);
      strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
      get_all(elf, shdr, strtab, data);
    }
  munmap(data, filesize(fd));
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
	  proceed(ac, av, a);
	  a++;
	}
      return (0);
    }
  proceed(ac, NULL, 0);
}
