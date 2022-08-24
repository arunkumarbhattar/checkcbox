//--------------------------------------------------------------------------//
// Additional bounds-safe interface options for functions that have         //
// different interfaces for array_ptr and nt_array_ptr args. Programmer can //
// choose to use these over the default bounds-safe interfaces.             //
//////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdlib_checked.h>
#include <string_checked.h>

#ifdef __checkcbox

#ifndef __TAINTED_EXTENSIONS_H
#define __TAINTED_EXTENSIONS_H

#pragma TLIB_SCOPE push
#pragma TLIB_SCOPE on
int c_isPointerToTaintedMem(void* pointer);

void* c_fetch_pointer_from_offset(const unsigned int pointer_offset);

int c_isTaintedPointerToTaintedMem(void* pointer);

void* c_fetch_sandbox_address();

unsigned int c_fetch_pointer_offset(void* pointer);

unsigned long c_fetch_sandbox_heap_address();

void* c_fetch_function_pointer(const char* const function_name);

unsigned long c_fetch_function_pointer_offset(const char* const function_name);

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

// default strncmp has a bounds-safe interface tnt_array_ptr;
// this option is for tarray_ptr
inline int __attribute__((__always_inline__))
t_strncmp_array_ptr(_TArray_ptr<const char> src : count(n), _TArray_ptr<const char> s2 : count(n), size_t n);

// default snprintf assumes nt_array_ptr for bounds-safe interface
// this option is for array_ptr
// clang does not inline functions that use va_list/va_start/va_end to
// access variable number of arguments.
_Unchecked static int
t_snprintf_array_ptr( _TArray_ptr<char> restrict s : count(n),
                       size_t n,
                       _TNt_array_ptr<const char> restrict format,
                       ...);
#pragma CHECKED_SCOPE pop
#pragma TLIB_SCOPE pop


#endif // guard 
#endif // TAINTED C
