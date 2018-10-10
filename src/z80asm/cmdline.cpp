//-----------------------------------------------------------------------------
// z80asm restart
// main code
// Copyright (C) Paulo Custodio, 2011-2018
// License: http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------
#include "pch.h"
#include "../config.h"

#ifndef Z88DK_VERSION
#define Z88DK_VERSION "build " __DATE__
#endif
#define COPYRIGHT   "(c) InterLogic 1993-2009, Paulo Custodio 2011-2018"

//-----------------------------------------------------------------------------
// global option flags
//-----------------------------------------------------------------------------
static int m_cpu = CPU_Z80;
static bool m_swap_ix_iy = false;
static bool m_verbose = false;
static bool m_map = false;
static bool m_symtable = false;
static bool m_list = false;
static bool m_globaldef = false;
static bool m_debug_info = false;
static bool m_update = false;
static bool m_make_bin = false;
static bool m_split_bin = false;
static bool m_relocatable = false;
static bool m_reloc_info = false;
static int m_filler = 0;
const char* m_bin_file = NULL;
const char* m_lib_file = NULL;
const char* m_output_dir = NULL;

static vector<string> m_inc_path, m_lib_path;

//-----------------------------------------------------------------------------
// parse numeric arguments
//-----------------------------------------------------------------------------
static int number_arg(const char *arg)
{
	char *end;
	const char *p = arg;
	long lval;
	int radix;
	char suffix = '\0';

	if (p[0] == '$') {
		p++;
		radix = 16;
	}
	else if (p[0] == '0' && tolower(p[1]) == 'x') {
		p += 2;
		radix = 16;
	}
	else if (isdigit(p[0]) && tolower(p[strlen(p) - 1]) == 'h') {
		suffix = p[strlen(p) - 1];
		radix = 16;
	}
	else {
		radix = 10;
	}

	lval = strtol(p, &end, radix);
	if (*end != suffix || errno == ERANGE || lval < 0 || lval > INT_MAX)
		return -1;
	else
		return (int)lval;
}

static void option_origin(const char *origin_arg)
{
	int value = number_arg(origin_arg);
	if (value < 0 || value > 0xFFFF) {
		cerr << "Error: invalid origin: " << origin_arg << endl;
		exit(EXIT_FAILURE);
	}
	else {
		set_origin_option(value);
	}
}

static void option_filler(const char *filler_arg)
{
	int value = number_arg(filler_arg);
	if (value < 0 || value > 0xFF) {
		cerr << "Error: invalid filler value: " << filler_arg << endl;
		exit(EXIT_FAILURE);
	}
	else {
		m_filler = value;
	}
}

//-----------------------------------------------------------------------------
// search directory path
//-----------------------------------------------------------------------------
static const char *search_path(const char *filename, vector<string>& dirs)
{
	// no dir list, return path
	if (dirs.empty())
		return path_canon(filename);

	// search in dir list
	for (auto& d : dirs) {
		const char *f = path_combine(d.c_str(), filename);
		if (file_exists(f))
			return f;
	}

	// not found, return original file name
	return path_canon(filename);
}

//-----------------------------------------------------------------------------
// parse valid CPU names
//-----------------------------------------------------------------------------
const char *_cpu_name(int cpu_type, bool is_symbol)
{
	switch (cpu_type) {
	case CPU_Z80: return "z80";
	case CPU_Z80_ZXN: return is_symbol ? "z80_zxn" : "z80-zxn";
	case CPU_Z180: return "z180";
	case CPU_R2K: return "r2k";
	case CPU_R3K: return "r3k";
	case CPU_TI83: return "ti83";
	case CPU_TI83PLUS: return "ti83plus";
	default: assert(0); return NULL;
	}
}

const char *cpu_name(int cpu_type)
{
	return _cpu_name(cpu_type, false);
}

const char *cpu_symbol(int cpu_type)
{
	return _cpu_name(cpu_type, true);
}

const char *cpu_define(int cpu_type)
{
	string symbol = "__CPU_" + string(cpu_symbol(cpu_type)) + "__";
	transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
	return spool_add(symbol.c_str());
}

int cpu_type(const char *cpu_name)
{
	string cpu(cpu_name);
	if (cpu == "z80") return CPU_Z80;
	else if (cpu == "z80-zxn") return CPU_Z80_ZXN;
	else if (cpu == "z180") return CPU_Z180;
	else if (cpu == "r2k") return CPU_R2K;
	else if (cpu == "r3k") return CPU_R3K;
	else if (cpu == "ti83") return CPU_TI83;
	else if (cpu == "ti83plus") return CPU_TI83PLUS;
	else return -1;
}

//-----------------------------------------------------------------------------
// run appmake
//-----------------------------------------------------------------------------
#define ZX_ORIGIN		 23760		// origin for unexpanded ZX Spectrum
#define ZX_ORIGIN_MIN	 ZX_ORIGIN
#define ZX_ORIGIN_MAX	 0xFFFF
#define ZX_APP_EXT		".tap"		// ZX Spectrum TAP file

#define ZX81_ORIGIN		 16514		// origin for ZX 81
#define ZX81_ORIGIN_MIN	 ZX81_ORIGIN
#define ZX81_ORIGIN_MAX  ZX81_ORIGIN
#define ZX81_APP_EXT	".P"		// ZX81 .P file

static bool m_appmake = false;

static const char* m_appmake_opts = "";
static const char* m_appmake_ext = "";
static int m_appmake_origin_min = -1;
static int m_appmake_origin_max = -1;

bool opt_appmake()
{
	return m_appmake;
}

void run_appmake(void)
{
	stringstream cmd;

	if (m_appmake) {
		Section *first_section = get_first_section(NULL);
		int origin = first_section->origin;
		if (origin < m_appmake_origin_min || origin > m_appmake_origin_max) {
			cerr << "Error: invalid origin: " << origin << endl;
			exit(EXIT_FAILURE);
		}
		else {
			const char *bin_filename = get_bin_filename(get_first_module(NULL)->filename);
			const char *out_filename = path_replace_ext(bin_filename, m_appmake_ext);

			cmd << "appmake " << m_appmake_opts << " -b \"" << bin_filename << "\" -o \""
				<< out_filename << "\" --org " << origin;

			if (opt_verbose())
				cout << cmd.str() << endl;

			int rv = system(cmd.str().c_str());
			if (rv != 0) {
				cerr << "Error: command failed: " << cmd.str() << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
}

static void option_appmake_zx(void)
{
	m_appmake = true;

	m_appmake_opts = "+zx";
	m_appmake_ext = ZX_APP_EXT;
	m_appmake_origin_min = ZX_ORIGIN_MIN;
	m_appmake_origin_max = ZX_ORIGIN_MAX;
	set_origin_option(ZX_ORIGIN);

	m_make_bin = true;
}

static void option_appmake_zx81(void)
{
	m_appmake = true;

	m_appmake_opts = "+zx81";
	m_appmake_ext = ZX81_APP_EXT;
	m_appmake_origin_min = ZX81_ORIGIN_MIN;
	m_appmake_origin_max = ZX81_ORIGIN_MAX;
	set_origin_option(ZX81_ORIGIN);

	m_make_bin = true;
}

//-----------------------------------------------------------------------------
// options interface
//-----------------------------------------------------------------------------

int opt_cpu()
{
	return m_cpu;
}

bool opt_swap_ix_iy()
{
	return m_swap_ix_iy;
}

bool opt_verbose()
{
	return m_verbose;
}

bool opt_map()
{
	return m_map;
}

bool opt_symtable()
{
	return m_symtable;
}

bool opt_list()
{
	return m_list;
}

bool opt_globaldef()
{
	return m_globaldef;
}

bool opt_debug_info()
{
	return m_debug_info;
}

bool opt_update()
{
	return m_update;
}

bool opt_make_bin()
{
	return m_make_bin;
}

bool opt_split_bin()
{
	return m_split_bin;
}

bool opt_relocatable()
{
	return m_relocatable;
}

bool opt_reloc_info()
{
	return m_reloc_info;
}

int opt_filler()
{
	return m_filler;
}

void opt_push_inc_path(const char *directory)
{
	m_inc_path.push_back(directory);
}

void opt_pop_inc_path()
{
	if (!m_inc_path.empty())
		m_inc_path.pop_back();
}

const char *opt_search_source(const char *filename)
{
	return search_path(filename, m_inc_path);
}

const char *opt_search_library(const char *filename)
{
	return search_path(filename, m_lib_path);
}

const char *opt_bin_file()
{
	if (m_make_bin)
		return m_bin_file;
	else
		return NULL;
}

const char *opt_consol_obj_file()
{
	if (m_make_bin)
		return NULL;
	else if (!m_bin_file)
		return NULL;
	else
		return get_obj_filename(m_bin_file);
}

const char *opt_lib_file()
{
	return m_lib_file;
}

const char *opt_output_dir()
{
	return m_output_dir;
}

// only for debug
extern "C" void _debug_set_symtable_list()
{
	m_symtable = true;
	m_list = true;
}

//-----------------------------------------------------------------------------
// parse command line options
//-----------------------------------------------------------------------------
static void usage()
{
	cout
		<< "Z80 Module Assembler " Z88DK_VERSION << endl
		<< COPYRIGHT << endl
		<< endl
		<< "Usage:" << endl
		<< "  z80asm [OPTIONS...] {FILE | @LIST}..." << endl
		<< endl;
}

static void exit_usage()
{
	usage();
	exit(EXIT_SUCCESS);
}

static void exit_help()
{
	usage();
	cout
		<< " Help options:" << endl
		<< "  -h, -?, --help      Show help options" << endl
		<< "  -v, --verbose       Be verbose" << endl
		<< endl
		<< " Environment options:" << endl
		<< "  -I, --inc-path arg  Append to include search path" << endl
		<< "  -L, --lib-path arg  Append to library search path" << endl
		<< "  -D, --define arg    Define a symbol" << endl
		<< endl
		<< " Assemble options:" << endl
		<< "  -m, --cpu arg       z80, z180, z80-zxn (ZX Next z80 variant)," << endl
		<< "                      r2k, r3k (Rabbit 2000 / 3000)," << endl
		<< "                      ti83, ti83plus (default: z80)" << endl
		<< "      --IXIY          Swap IX and IY" << endl
		<< "  -d, --update        Assemble only updated files" << endl
		<< "  -s, --symtable      Generate module symbol table" << endl
		<< "  -l, --list          Generate module list file" << endl
		<< endl
		<< " Link options:" << endl
		<< "  -b, --make-bin      Assemble and link" << endl
		<< "      --split-bin     One binary file per section" << endl
		<< "      --filler arg    Filler byte for DEFS" << endl
		<< "  -r, --origin arg    Link at origin address" << endl
		<< "  -R, --relocatable   Generate relocation code" << endl
		<< "      --reloc-info    Generate relocation information" << endl
		<< "  -m, --map           Generate map file" << endl
		<< "  -g, --globaldef     Generate global definition file" << endl
		<< "      --debug         Debug info in map file" << endl
		<< endl
		<< " Libraries options:" << endl
		<< "  -x, --make-lib arg  Create library" << endl
		<< "  -i, --link-lib arg  Link with library" << endl
		<< endl
		<< " Output options:" << endl
		<< "  -O, --out-dir arg   Output directory" << endl
		<< "  -o, --output arg    Output file" << endl
		<< endl
		<< " Appmake options:" << endl
		<< "  +zx81               Generate .p file, origin at 16514" << endl
		<< "  +zx                 Generate .tap file, origin at 23760 or" << endl
		<< "                      above Ramtop with - rORG > 24000" << endl
		<< endl;
	exit(EXIT_SUCCESS);
}

static void opt_define(const string& arg)
{
	static regex symbol_re("[_[:alpha:]][_[:alnum:]]*");
	if (!regex_match(arg, symbol_re)) {
		cerr << "Error: illegal identifier: " << arg << endl;
		exit(EXIT_FAILURE);
	}

	define_static_def_sym(arg.c_str(), 1);
}

static bool option_arg(int& i, int argc, char *argv[],
	const string& short_opt, const string& long_opt,
	string& arg)
{
	string opt = argv[i];
	arg.clear();

	if (opt == long_opt) {
		i++;
		if (i < argc) {
			arg = expand_environment_variables(argv[i]);
			return true;
		}
		else {
			cerr << "Error: option requires argument: " << opt << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (opt.substr(0, short_opt.length() + 1) == short_opt + "=") {
		arg = expand_environment_variables(opt.substr(short_opt.length() + 1).c_str());
		return true;
	}
	else if (opt.substr(0, long_opt.length() + 1) == long_opt + "=") {
		arg = expand_environment_variables(opt.substr(long_opt.length() + 1).c_str());
		return true;
	}
	else if (opt.substr(0, short_opt.length()) == short_opt ) {
		arg = expand_environment_variables(opt.substr(short_opt.length()).c_str());
		return true;
	}
	else {
		return false;
	}
}

static bool parse_cmdline(int argc, char *argv[])
{
	if (argc == 1)
		exit_usage();

	bool has_files = false;

	for (int i = 1; i < argc; i++) {
		string opt = argv[i];
		string arg;

		if (argv[i][0] == '-') {
			if (opt == "--") {
				i++;
				while (i < argc) {
					process_arg_file(argv[i]);
					has_files = true;
					i++;
				}
			}
			else if (opt == "-?" || opt == "-h" || opt == "--help") {
				exit_help();
			}
			else if (opt == "-v" || opt == "--verbose") {
				m_verbose = true;
			}
			else if (opt == "--map") {
				m_map = true;
			}
			else if (opt == "-s" || opt == "--symtable") {
				m_symtable = true;
			}
			else if (opt == "-l" || opt == "--list") {
				m_list = true;
			}
			else if (opt == "-g" || opt == "--globaldef") {
				m_globaldef = true;
			}
			else if (opt == "--debug") {
				m_debug_info = true;
				m_map = true;
			}
			else if (opt == "-IXIY" || opt == "-IYIX" || opt == "--IXIY" || opt == "--IYIX") {
				m_swap_ix_iy = true;
			}
			else if (opt == "-d" || opt == "--update") {
				m_update = true;
			}
			else if (opt == "-b" || opt == "--make-bin") {
				m_make_bin = true;
			}
			else if (opt == "--split-bin") {
				m_split_bin = true;
			}
			else if (opt == "-R" || opt == "--relocatable") {
				m_relocatable = true;
			}
			else if (opt == "--reloc-info") {
				m_reloc_info = true;
			}
			else if (option_arg(i, argc, argv, "-I", "--inc-path", arg)) {
				m_inc_path.push_back(arg);
			}
			else if (option_arg(i, argc, argv, "-L", "--lib-path", arg)) {
				m_lib_path.push_back(arg);
			}
			else if (option_arg(i, argc, argv, "-D", "--define", arg)) {
				opt_define(arg);
			}
			else if (option_arg(i, argc, argv, "-m", "--cpu", arg)) {
				if (arg.empty() || arg[0] == '-') {	// if next is an option -> --map
					if (!arg.empty())
						i--;
					m_map = true;
				}
				else {
					int cpu = cpu_type(arg.c_str());
					if (cpu < 0) {
						cerr << "Error: invalid cpu: " << arg << endl;
						return false;
					}
					else {
						m_cpu = cpu;
					}
				}
			}
			else if (option_arg(i, argc, argv, "--filler", "--filler", arg)) {
				option_filler(arg.c_str());
			}
			else if (option_arg(i, argc, argv, "-r", "--origin", arg)) {
				option_origin(arg.c_str());
			}
			else if (option_arg(i, argc, argv, "-o", "--output", arg)) {
				m_bin_file = spool_add(arg.c_str());
			}
			else if (option_arg(i, argc, argv, "-O", "--out-dir", arg)) {
				m_output_dir = spool_add(path_canon(arg.c_str()));
				path_mkdir(m_output_dir);
			}
			else if (option_arg(i, argc, argv, "-x", "--make-lib", arg)) {
				m_lib_file = spool_add(arg.c_str());
			}
			else if (option_arg(i, argc, argv, "-i", "--link-lib", arg)) {
				GetLibfile(arg.c_str());
			}
			else {
				cerr << "Error: illegal option: " << argv[i] << endl;
				return false;
			}
		}
		else if (argv[i][0] == '+') {
			if (opt == "+zx") {
				option_appmake_zx();
			}
			else if (opt == "+zx81") {
				option_appmake_zx81();
			}
			else {
				cerr << "Error: illegal option: " << argv[i] << endl;
				return false;
			}
		}
		else {
			process_arg_file(argv[i]);
			has_files = true;
		}
	}

	if (!has_files) {
		cerr << "Error: source filename missing" << endl;
		return false;
	}

	return true;
}

int zmain(int argc, char *argv[])
{
	model_init();			// init global data
	init_libraryhdr();		// initialise to no library files
	init_macros();

	if (!parse_cmdline(argc, argv))
		exit(EXIT_FAILURE);
	else
		return z80asm_main();
}
