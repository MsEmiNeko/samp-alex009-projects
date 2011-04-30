struct section {
	const char	*name;		/* section name */
	Elf_Scn		*scn;		/* section scn */
	uint64_t	 off;		/* section offset */
	uint64_t	 sz;		/* section size */
	uint64_t	 entsize;	/* section entsize */
	uint64_t	 align;		/* section alignment */
	uint64_t	 type;		/* section type */
	uint64_t	 flags;		/* section flags */
	uint64_t	 addr;		/* section virtual addr */
	uint32_t	 link;		/* section link ndx */
	uint32_t	 info;		/* section info ndx */
};

struct dumpop {
	size_t		 sn;		/* section index */
#define HEX_DUMP	0x0001
#define STR_DUMP	0x0002
	int		 op;		/* dump op type */
	STAILQ_ENTRY(dumpop) dumpop_list;
};

struct readelf {
	const char	 *filename;	/* current processing file. */
	int		  options;	/* command line options. */
	int		  flags;	/* run control flags. */
	int		  dop;		/* dwarf dump options. */
	Elf		 *elf;		/* underlying ELF descriptor. */
	Elf		 *ar;		/* archive ELF descriptor. */
	Dwarf_Debug	  dbg;		/* DWARF handle. */
	GElf_Ehdr	  ehdr;		/* ELF header. */
	int		  ec;		/* ELF class. */
	size_t		  shnum;	/* #sections. */
	struct section	 *vd_s;		/* Verdef section. */
	struct section	 *vn_s;		/* Verneed section. */
	struct section	 *vs_s;		/* Versym section. */
	uint16_t	 *vs;		/* Versym array. */
	int		  vs_sz;	/* Versym array size. */
	const char	**vname;	/* Version name array. */
	int		  vname_sz;	/* Size version name array. */
	struct section	 *sl;		/* list of sections. */
	STAILQ_HEAD(, dumpop) v_dumpop; /* list of dump ops. */
	uint64_t	(*dw_read)(Elf_Data *, uint64_t *, int);
	uint64_t	(*dw_decode)(uint8_t **, int);
};

static void load_sections(struct readelf *re)
{
	struct section	*s;
	const char	*name;
	Elf_Scn		*scn;
	GElf_Shdr	 sh;
	size_t		 shstrndx, ndx;
	int		 elferr;

	/* Allocate storage for internal section list. */
	if (!elf_getshnum(re->elf, &re->shnum)) {
		warnx("elf_getshnum failed: %s", elf_errmsg(-1));
		return;
	}
	if (re->sl != NULL)
		free(re->sl);
	if ((re->sl = calloc(re->shnum, sizeof(*re->sl))) == NULL)
		err(EX_SOFTWARE, "calloc failed");

	/* Get the index of .shstrtab section. */
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

static void dump_elf(struct readelf *re)
{

	/* Fetch ELF header. No need to continue if it fails. */
	if (gelf_getehdr(re->elf, &re->ehdr) == NULL) {
		warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
		return;
	}
	if ((re->ec = gelf_getclass(re->elf)) == ELFCLASSNONE) {
		warnx("gelf_getclass failed: %s", elf_errmsg(-1));
		return;
	}
	if (re->ehdr.e_ident[EI_DATA] == ELFDATA2MSB) {
		re->dw_read = _read_msb;
		re->dw_decode = _decode_msb;
	} else {
		re->dw_read = _read_lsb;
		re->dw_decode = _decode_lsb;
	}

	if (re->options & ~RE_H)
		load_sections(re);
	if ((re->options & RE_VV) || (re->options && RE_S))
		search_ver(re);
	if (re->options & RE_H)
		dump_ehdr(re);
	if (re->options & RE_L)
		dump_phdr(re);
	if (re->options & RE_SS)
		dump_shdr(re);
	if (re->options & RE_D)
		dump_dynamic(re);
	if (re->options & RE_R)
		dump_reloc(re);
	if (re->options & RE_S)
		dump_symtabs(re);
	if (re->options & RE_N)
		dump_notes(re);
	if (re->options & RE_II)
		dump_hash(re);
	if (re->options & RE_X)
		hex_dump(re);
	if (re->options & RE_P)
		str_dump(re);
	if (re->options & RE_VV)
		dump_ver(re);
	if (re->options & RE_AA)
		dump_arch_specific_info(re);
	if (re->options & RE_W)
		dump_dwarf(re);
}

static void dump_ar(struct readelf *re, int fd)
{
	Elf_Arsym *arsym;
	Elf_Arhdr *arhdr;
	Elf_Cmd cmd;
	Elf *e;
	size_t sz;
	off_t off;
	int i;

	re->ar = re->elf;

	if (re->options & RE_C) {
		if ((arsym = elf_getarsym(re->ar, &sz)) == NULL) {
			warnx("elf_getarsym() failed: %s", elf_errmsg(-1));
			goto process_members;
		}
		printf("Index of archive %s: (%ju entries)\n", re->filename,
		    (uintmax_t) sz - 1);
		off = 0;
		for (i = 0; (size_t) i < sz; i++) {
			if (arsym[i].as_name == NULL)
				break;
			if (arsym[i].as_off != off) {
				off = arsym[i].as_off;
				if (elf_rand(re->ar, off) != off) {
					warnx("elf_rand() failed: %s",
					    elf_errmsg(-1));
					continue;
				}
				if ((e = elf_begin(fd, ELF_C_READ, re->ar)) ==
				    NULL) {
					warnx("elf_begin() failed: %s",
					    elf_errmsg(-1));
					continue;
				}
				if ((arhdr = elf_getarhdr(e)) == NULL) {
					warnx("elf_getarhdr() failed: %s",
					    elf_errmsg(-1));
					elf_end(e);
					continue;
				}
				printf("Binary %s(%s) contains:\n",
				    re->filename, arhdr->ar_name);
			}
			printf("\t%s\n", arsym[i].as_name);
		}
		if (elf_rand(re->ar, SARMAG) != SARMAG) {
			warnx("elf_rand() failed: %s", elf_errmsg(-1));
			return;
		}
	}

process_members:

	if ((re->options & ~RE_C) == 0)
		return;

	cmd = ELF_C_READ;
	while ((re->elf = elf_begin(fd, cmd, re->ar)) != NULL) {
		if ((arhdr = elf_getarhdr(re->elf)) == NULL) {
			warnx("elf_getarhdr() failed: %s", elf_errmsg(-1));
			goto next_member;
		}
		if (strcmp(arhdr->ar_name, "/") == 0 ||
		    strcmp(arhdr->ar_name, "//") == 0)
			goto next_member;
		printf("\nFile: %s(%s)\n", re->filename, arhdr->ar_name);
		dump_elf(re);

	next_member:
		cmd = elf_next(re->elf);
		elf_end(re->elf);
	}
	re->elf = re->ar;
}

static void dump_object(struct readelf *re)
{
	int fd;

	if ((fd = open(re->filename, O_RDONLY)) == -1) {
		warn("open %s failed", re->filename);
		return;
	}

	if ((re->flags & DISPLAY_FILENAME) != 0)
		printf("\nFile: %s\n", re->filename);

	if ((re->elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
		warnx("elf_begin() failed: %s", elf_errmsg(-1));
		return;
	}

	switch (elf_kind(re->elf)) {
	case ELF_K_NONE:
		warnx("Not an ELF file.");
		return;
	case ELF_K_ELF:
		dump_elf(re);
		break;
	case ELF_K_AR:
		dump_ar(re, fd);
		break;
	default:
		warnx("Internal: libelf returned unknown elf kind.");
		return;
	}

	elf_end(re->elf);
}