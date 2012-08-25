#ifndef STACK_PRINTER
#define STACK_PRINTER

#ifdef _WIN32
#define PLATFORM_WINDOWS
#else
	#ifdef linux
		#define PLATFORM_LINUX
	#endif
#endif

#ifdef PLATFORM_WINDOWS
#include "StackWalker/StackWalker.h"
#endif

#ifdef PLATFORM_LINUX
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>
#endif

class StackPrinter {
private:

#ifdef PLATFORM_WINDOWS
StackWalker sw;
#endif

public:
	StackPrinter();
	void print();
};

#endif