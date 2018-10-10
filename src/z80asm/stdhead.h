//-----------------------------------------------------------------------------
// z80asm restart
// standard headers
// Copyright (C) Paulo Custodio, 2011-2018
// License: http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------
#pragma once

#include <exception>
#include <stdexcept>
using std::exception;
using std::runtime_error;

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::istream;
using std::ios;
using std::ofstream;
using std::ostream;
using std::streambuf;
using std::stringstream;

#include <string>
using std::string;
using std::to_string;

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <unordered_map>
using std::unordered_map;

#include <unordered_set>
using std::unordered_set;

#include <algorithm>
using std::find_if;
using std::transform;

#include <utility>
using std::make_pair;

#include <regex>
using std::regex;

#include <cassert>
#include <cerrno>
#include <cctype>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#if 0
#ifdef _WIN32
#include <windows.h>
#else // POSIX
#include <unistd.h>
#endif
#endif

#include <sys/stat.h>
