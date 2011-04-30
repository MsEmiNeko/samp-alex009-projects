/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#ifdef WIN32

#include <windows.h>

// thanks to listener (xLiveLess)
void GetSectionDataByName(char* name,unsigned long* base,unsigned long* size)
{
	char * pszSectionName;
	BYTE * pImageBase = reinterpret_cast<BYTE *>(0x400000); 
	PIMAGE_DOS_HEADER pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER> (0x400000);
    PIMAGE_NT_HEADERS pNtHeader  = reinterpret_cast<PIMAGE_NT_HEADERS> (pImageBase+pDosHeader->e_lfanew);
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeader);

    for (int iSection = 0; iSection < pNtHeader->FileHeader.NumberOfSections; ++iSection, ++pSection) 
	{
        pszSectionName = reinterpret_cast<char *>(pSection->Name);
        if (!strcmp (pszSectionName,name)) 
		{
			*base = 0x400000 + pSection->VirtualAddress;
			*size = (pSection->Misc.VirtualSize + 4095) & ~4095; 
			break;
		}
    }
}

#else

#include "unix.h"

/*

static void
load_sections(struct readelf *re)
{
	struct section	*s;
	const char	*name;
	Elf_Scn		*scn;
	GElf_Shdr	 sh;
	size_t		 shstrndx, ndx;
	int		 elferr;

	// Allocate storage for internal section list.
	if (!elf_getshnum(re->elf, &re->shnum)) {
		warnx("elf_getshnum failed: %s", elf_errmsg(-1));
		return;
	}
	if (re->sl != NULL)
		free(re->sl);
	if ((re->sl = calloc(re->shnum, sizeof(*re->sl))) == NULL)
		err(EX_SOFTWARE, "calloc failed");

	// Get the index of .shstrtab section.
	if (!elf_getshstrndx(re->elf, &shstrndx)) {
		warnx("elf_getshstrndx failed: %s", elf_errmsg(-1));
		return;
	}

	if ((scn = elf_getscn(re->elf, 0)) == NULL) {
		warnx("elf_getscn failed: %s", elf_errmsg(-1));
		return;
	}

	(void) elf_errno();
	do {
		if (gelf_getshdr(scn, &sh) == NULL) {
			warnx("gelf_getshdr failed: %s", elf_errmsg(-1));
			(void) elf_errno();
			continue;
		}
		if ((name = elf_strptr(re->elf, shstrndx, sh.sh_name)) == NULL) {
			(void) elf_errno();
			name = "ERROR";
		}
		if ((ndx = elf_ndxscn(scn)) == SHN_UNDEF) {
			if ((elferr = elf_errno()) != 0)
				warnx("elf_ndxscn failed: %s",
				    elf_errmsg(elferr));
			continue;
		}
		if (ndx >= re->shnum) {
			warnx("section index of '%s' out of range", name);
			continue;
		}
		s = &re->sl[ndx];
		s->name = name;
		s->scn = scn;
		s->off = sh.sh_offset;
		s->sz = sh.sh_size;
		s->entsize = sh.sh_entsize;
		s->align = sh.sh_addralign;
		s->type = sh.sh_type;
		s->flags = sh.sh_flags;
		s->addr = sh.sh_addr;
		s->link = sh.sh_link;
		s->info = sh.sh_info;
	} while ((scn = elf_nextscn(re->elf, scn)) != NULL);
	elferr = elf_errno();
	if (elferr != 0)
		warnx("elf_nextscn failed: %s", elf_errmsg(elferr));
}

*/

#endif