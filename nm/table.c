/*
** table.c for nm in /home/erwan.simon/Code/teck/C/PSU_2016_nmobjdump
** 
** Made by Erwan Simon
** Login   <erwan.simon@epitech.net>
** 
** Started on  Wed Feb 22 16:33:59 2017 Erwan Simon
** Last update Sun Feb 26 14:49:31 2017 Erwan Simon
*/

#include <elf.h>
#include "nm.h"

static t_table	get_match[] = {
  { STB_LOCAL, STT_TLS, SHT_NOBITS, 1027, 'b' },
  { STB_LOCAL, STT_NOTYPE, SHT_NOBITS, 3, 'b' },
  { STB_LOCAL, STT_OBJECT, SHT_NOBITS, 3, 'b' },
  { STB_GLOBAL, STT_OBJECT, SHT_NOBITS, 3, 'B' },
  { STB_GLOBAL, STT_NOTYPE, SHT_NOBITS, 3, 'B' },
  { STB_LOCAL, STT_TLS, SHT_PROGBITS, 1027, 'd' },
  { STB_LOCAL, STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
  { STB_LOCAL, STT_OBJECT, SHT_PROGBITS, 3, 'd' },
  { STB_LOCAL, STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
  { STB_GLOBAL, STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
  { STB_GLOBAL, STT_OBJECT, SHT_PROGBITS, 3, 'D' },
  { STB_GLOBAL, STT_LOOS, SHT_PROGBITS, 6, 'i' },
  { STB_LOCAL, STT_LOOS, SHT_PROGBITS, 6, 'i' },
  { STB_LOCAL, STT_OBJECT, SHT_PROGBITS, 0, 'n' },
  { STB_LOCAL, STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
  { STB_LOCAL, STT_OBJECT, SHT_NOTE, 2, 'r' },
  { STB_LOCAL, STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
  { STB_LOCAL, STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
  { STB_LOCAL, STT_OBJECT, SHT_PROGBITS, 2, 'r' },
  { STB_LOCAL, STT_OBJECT, SHT_PROGBITS, 50, 'r' },
  { STB_GLOBAL, STT_OBJECT, SHT_PROGBITS, 2, 'R' },
  { STB_LOCAL, STT_NOTYPE, SHT_PROGBITS, 6, 't' },
  { STB_LOCAL, STT_NOTYPE, SHT_INIT_ARRAY, 3, 't' },
  { STB_LOCAL, STT_FUNC, SHT_PROGBITS, 6, 't' },
  { STB_LOCAL, STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
  { STB_LOCAL, STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
  { STB_GLOBAL, STT_FUNC, SHT_PROGBITS, 6, 'T' },
  { STB_GLOBAL, STT_FUNC, SHT_NULL, 0, 'U' }
};

char	get_weak(Elf64_Sym *sym)
{
  if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      if (sym->st_shndx != SHN_UNDEF)
	return ('V');
      return ('v');
    }
  if (sym->st_shndx != SHN_UNDEF)
    return ('W');
  return ('w');
}

char	preliminary(Elf64_Sym *sym)
{
  if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL
      && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
      && sym->st_shndx == SHN_COMMON)
    return ('C');
  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    return ('U');
  return ('\0');
}

char	get_letter(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  int	a;

  a = 0;
  if (preliminary(sym) != '\0')
    return (preliminary(sym));
  if (sym->st_shndx != SHN_ABS && sym->st_shndx != SHN_COMMON)
    {
      while (a != sizeof(get_match) / sizeof(*get_match))
	{
	  if (ELF64_ST_BIND(sym->st_info) == get_match[a].range
	      && ELF64_ST_TYPE(sym->st_info) == get_match[a].info
	      && shdr[sym->st_shndx].sh_type == get_match[a].type
	      && shdr[sym->st_shndx].sh_flags == get_match[a].flags)
	    return (get_match[a].letter);
	  a++;
	}
      if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	return ('U');
    }
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    return (get_weak(sym));
  if (sym->st_shndx == SHN_ABS)
    return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'a' : 'A');
  return ('?');
}
