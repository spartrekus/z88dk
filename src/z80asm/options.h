//-----------------------------------------------------------------------------
// Z88DK Z80 Module Assembler
// Parse command line options
// Copyright (C) Paulo Custodio, 2011-2018
// License: http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "utarray.h"
#include "strutil.h"

#include "cmdline.h"

/*-----------------------------------------------------------------------------
*   CPU type
*----------------------------------------------------------------------------*/

#define CPU_ZILOG	(CPU_Z80 | CPU_Z80_ZXN| CPU_Z180)
#define CPU_RABBIT	(CPU_R2K | CPU_R3K)
#define CPU_ALL		(CPU_ZILOG | CPU_RABBIT)
#define CPU_NOT_Z80	(CPU_ALL & ~(CPU_Z80 | CPU_Z80_ZXN))

/*-----------------------------------------------------------------------------
*   Assembler standard library
*----------------------------------------------------------------------------*/
#define Z80ASM_LIB	"z80asm-%s-%s.lib"
#define SWAP_IX_IY_NAME	(opt_swap_ix_iy() ? "ixiy" : "")

/*-----------------------------------------------------------------------------
*   Parse command line, set options, including argv_files with list of
*	input files, including parsing of '@' lists
*----------------------------------------------------------------------------*/
const char *expand_environment_variables(const char *arg);
void process_arg_file(char *filename);
void include_z80asm_lib();
void define_assembly_defines();

/*-----------------------------------------------------------------------------
*   Change extension of given file name, return pointer to file name in
*	strpool
*	Extensions may be changed by options.
*----------------------------------------------------------------------------*/
extern const char *get_asm_filename(const char *filename );
extern const char *get_list_filename(const char *filename );
extern const char *get_obj_filename(const char *filename );
extern const char *get_def_filename(const char *filename );
extern const char *get_err_filename(const char *filename );
extern const char *get_bin_filename(const char *filename );
extern const char *get_lib_filename(const char *filename );
extern const char *get_sym_filename(const char *filename );
extern const char *get_map_filename(const char *filename);
extern const char *get_reloc_filename(const char *filename);

#ifdef __cplusplus
} // extern "C"
#endif
