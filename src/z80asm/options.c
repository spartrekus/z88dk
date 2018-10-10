//-----------------------------------------------------------------------------
// Z88DK Z80 Module Assembler
// Parse command line options
// Copyright (C) Paulo Custodio, 2011-2018
// License: http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------

#include "../config.h"
#include "../portability.h"

#include "errors.h"
#include "fileutil.h"
#include "hist.h"
#include "model.h"
#include "options.h"
#include "srcfile.h"
#include "str.h"
#include "strutil.h"
#include "symtab.h"
#include "utarray.h"
#include "z80asm.h"
#include "die.h"

#include "cmdline.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

/* default file name extensions */
#define FILEEXT_ASM     ".asm"    
#define FILEEXT_LIST    ".lis"    
#define FILEEXT_OBJ     ".o"	  
#define FILEEXT_DEF     ".def"    
#define FILEEXT_ERR     ".err"    
#define FILEEXT_BIN     ".bin"    
#define FILEEXT_LIB     ".lib"    
#define FILEEXT_SYM     ".sym"    
#define FILEEXT_MAP     ".map"    
#define FILEEXT_RELOC   ".reloc"  

/* declare functions */
static const char *search_z80asm_lib();

static void expand_source_glob(const char *pattern);
static void expand_list_glob(const char *filename);

static char *replace_str(const char *str, const char *old, const char *new);

/*-----------------------------------------------------------------------------
*   process a file
*----------------------------------------------------------------------------*/

/* search for the first file in path, with the given extension,
* with .asm extension and with .o extension
* if not found, return original file */
static const char *search_source(const char *filename)
{
	const char *f;

	if (file_exists(filename))
		return filename;

	f = opt_search_source(filename);
	if (file_exists(f))
		return f;

	f = get_asm_filename(filename);
	if (file_exists(f))
		return f;

	f = opt_search_source(f);
	if (file_exists(f))
		return f;

	f = get_obj_filename(filename);
	if (file_exists(f))
		return f;

	f = opt_search_source(f);
	if (file_exists(f))
		return f;

	error_read_file(filename);
	return filename;
}

void process_arg_file(char *filename )
{
	cstr_strip(filename);
	switch (filename[0])
	{
	case '-':		/* Illegal source file name */
	case '+':
		error_illegal_src_filename(filename);
		break;

	case '\0':		/* no file */
		break;

	case '@':		/* file list */
		filename++;						/* point to after '@' */
		cstr_strip(filename);
		filename = (char *)expand_environment_variables(filename);
		expand_list_glob(filename);
		break;
	case ';':     /* comment */
	case '#':
		break;
	default:
		filename = (char *)expand_environment_variables(filename);
		expand_source_glob(filename);
	}
}

void expand_source_glob(const char *pattern)
{
	if (strpbrk(pattern, "*?") != NULL) {		// is a pattern
		argv_t *files = path_find_glob(pattern);

		if (argv_len(files) == 0)
			error_glob_no_files(pattern);		// error if pattern matched no file

		for (char **p = argv_front(files); *p; p++) {
			argv_push(argv_files, search_source(*p));
		}

		argv_free(files);
	}
	else {
		argv_push(argv_files, search_source(pattern));
	}
}

void expand_list_glob(const char *filename)
{
	if (strpbrk(filename, "*?") != NULL) {		// is a pattern
		argv_t *files = path_find_glob(filename);
		for (char **p = argv_front(files); *p; p++) {
			char *filename = *p;
			src_push();
			{
				char *line;

				// append the directoy of the list file to the include path	and remove it at the end
				opt_push_inc_path(path_dir(filename));

				if (src_open(filename)) {
					while ((line = src_getline()) != NULL)
						process_arg_file(line);
				}

				// finished assembly, remove dirname from include path
				opt_pop_inc_path();
			}
			src_pop();
		}
		argv_free(files);
	}
	else {
		src_push();
		{
			char *line;

			// append the directoy of the list file to the include path	and remove it at the end
			opt_push_inc_path(path_dir(filename));

			if (src_open(filename)) {
				while ((line = src_getline()) != NULL)
					process_arg_file(line);
			}

			// finished assembly, remove dirname from include path
			opt_pop_inc_path();
		}
		src_pop();
	}
}

/*-----------------------------------------------------------------------------
*   replace environment variables in filenames
*----------------------------------------------------------------------------*/

const char *expand_environment_variables(const char *arg)
{
	char  *ptr, *nval = NULL;
	char  *rep, *start;
	char  *value = strdup(arg);
	char   varname[300];
	const char  *ret;

	start = value;
	while ((ptr = strchr(start, '$')) != NULL) 
	{
		if (*(ptr + 1) == '{') 
		{
			char  *end = strchr(ptr + 1, '}');

			if (end != NULL) {
				snprintf(varname, sizeof(varname), "%.*s", (int)(end - ptr - 2), ptr + 2);
				rep = getenv(varname);
				if (rep == NULL) 
				{
					rep = "";
				}

				snprintf(varname, sizeof(varname), "%.*s", (int)(end - ptr + 1), ptr);
				nval = replace_str(value, varname, rep);
				free(value);
				value = nval;
				start = value + (ptr - start);
			}
		}
		else 
		{
			start++;
		}
	}

	ret = spool_add(value);		// free memory, return pooled string
	free(value);
	return ret;
}

/* From: http://creativeandcritical.net/str-replace-c/ */
static char *replace_str(const char *str, const char *old, const char *new)
{
	char *ret, *r;
	const char *p, *q;
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(new);

	if (oldlen != newlen) 
	{
		for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
			count++;
		/* this is undefined if p - str > PTRDIFF_MAX */
		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	}
	else
		retlen = strlen(str);

	ret = malloc(retlen + 1);

	for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) 
	{
		/* this is undefined if q - p > PTRDIFF_MAX */
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, new, newlen);
		r += newlen;
	}
	strcpy(r, p);

	return ret;
}

void define_assembly_defines()
{
	define_static_def_sym(cpu_define(opt_cpu()), 1);

	if (opt_swap_ix_iy()) {
		define_static_def_sym("__SWAP_IX_IY__", 1);
	}
}

/*-----------------------------------------------------------------------------
*   Change extension of given file name, return pointer to file name in
*	strpool
*	Extensions may be changed by options.
*----------------------------------------------------------------------------*/
static const char *path_prepend_output_dir(const char *filename)
{
	char path[FILENAME_MAX];
	if (opt_output_dir()) {
		if (isalpha(filename[0]) && filename[1] == ':')	// it's a win32 absolute path
			snprintf(path, sizeof(path), "%s/%c/%s", 
				opt_output_dir(), filename[0], filename + 2);
		else
			snprintf(path, sizeof(path), "%s/%s", 
				opt_output_dir(), filename);
		return spool_add(path);
	}
	else {
		return filename;
	}
}

const char *get_list_filename(const char *filename )
{
	return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_LIST));
}

const char *get_def_filename(const char *filename )
{
    return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_DEF));
}

const char *get_err_filename(const char *filename )
{
    return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_ERR));
}

const char *get_bin_filename(const char *filename )
{
    return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_BIN));
}

const char *get_lib_filename(const char *filename )
{
    return path_replace_ext(filename, FILEEXT_LIB);
}

const char *get_sym_filename(const char *filename )
{
    return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_SYM));
}

const char *get_map_filename(const char *filename)
{
	return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_MAP));
}

const char *get_reloc_filename(const char *filename)
{
	return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_RELOC));
}

const char *get_asm_filename(const char *filename)
{
	return path_replace_ext(filename, FILEEXT_ASM);
}

const char *get_obj_filename(const char *filename )
{
	return path_prepend_output_dir(path_replace_ext(filename, FILEEXT_OBJ));
}

/*-----------------------------------------------------------------------------
*   z80asm standard library
*	search in current die, then in exe path, then in exe path/../lib, then in ZCCCFG/..
*	Ignore if not found, probably benign - user will see undefined symbols
*	__z80asm__xxx if the library routines are called
*----------------------------------------------------------------------------*/
void include_z80asm_lib()
{
	const char *library = search_z80asm_lib();

	if (library != NULL)
		GetLibfile(library);
}

static const char *check_library(const char *lib_name)
{
	if (file_exists(lib_name))
		return lib_name;
	
	if (opt_verbose())
		printf("Library '%s' not found\n", path_canon(lib_name));

	return NULL;
}

static const char *search_z80asm_lib()
{
	STR_DEFINE(lib_name_str, STR_SIZE);
	const char *lib_name;
	STR_DEFINE(f, STR_SIZE);
	const char *ret;

	/* Build libary file name */
	Str_sprintf(lib_name_str, Z80ASM_LIB, cpu_symbol(opt_cpu()), SWAP_IX_IY_NAME);
	lib_name = spool_add(Str_data(lib_name_str));

	/* try to read from current directory */
	if (check_library(lib_name))
		return lib_name;

	/* try to read from PREFIX/lib */
	Str_sprintf(f, "%s/lib/%s", PREFIX, lib_name);
	ret = spool_add(Str_data(f));
	if (check_library(ret))
		return ret;

	/* try to read form -L path */
	ret = opt_search_library(get_lib_filename(lib_name));
	if (strcmp(ret, lib_name) != 0) {		// found one in path
		if (check_library(ret))
			return ret;
	}

	/* try to read from ZCCCFG/.. */
	Str_sprintf(f, "${ZCCCFG}/../%s", lib_name);
	ret = expand_environment_variables(Str_data(f));
	if (check_library(ret))
		return ret;

	return NULL;		/* not found */
}
