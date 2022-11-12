//--------------------------------------------------------------------------//
// Additional bounds-safe interface options for functions that have         //
// different interfaces for array_ptr and nt_array_ptr args. Programmer can //
// choose to use these over the default bounds-safe interfaces.             //
//////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdlib_checked.h>
#include <string_checked.h>
#include "stdio_tainted.h"
#include "stdlib_tainted.h"
#include "string_tainted.h"

#  define SIZE_MAX		(18446744073709551615UL)
#ifdef __checkcbox

#ifndef __TAINTED_EXTENSIONS_H
#define __TAINTED_EXTENSIONS_H

#pragma TLIB_SCOPE push
#pragma TLIB_SCOPE on
int c_isPointerToTaintedMem(void* pointer);

void* c_fetch_pointer_from_offset(const unsigned int pointer_offset);

void* c_ConditionalTaintedOff2Ptr(const unsigned long pointer_offset);

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
_TLIB static _TNt_array_ptr<char> string_tainted_malloc(size_t sz) : count(sz) _Unchecked{
  if(sz >= SIZE_MAX)
    return NULL;
  _TArray_ptr<char> p : count(sz+1) = (_TArray_ptr<char>)t_malloc(sz + 1);
  if (p != NULL)
    p[sz] = 0;
  return _Tainted_Assume_bounds_cast<_TNt_array_ptr<char>>(p, count(sz));
}

_TLIB static _Ptr<char> StrMalloc(size_t sz)
     _Unchecked {
  if (sz >= SIZE_MAX)
    return NULL;
  char *p = (char *)malloc<char>(sz + 1);
  if (p != NULL)
    p[sz] = 0;
  return _Assume_bounds_cast<_Nt_array_ptr<char>>(p, count(sz));
}

static _TPtr<char> TNtStrRealloc(_TPtr<char> old_mem, size_t sz)
    _Unchecked {
  if (sz >= SIZE_MAX)
    return NULL;
  _TPtr<char> p = t_realloc<char>(old_mem, sz + 1);
  if (p != NULL)
    p[sz] = 0;
  return p;
}
static _TPtr<char> GlobalTaintedAdaptorStr = NULL;

_TLIB _Unchecked
    static _TPtr<char>
        StaticCheckedToTStrAdaptor(_Nt_array_ptr<char> Ip )
{
  int Iplen = strlen((const char*)Ip);
  GlobalTaintedAdaptorStr = TNtStrRealloc(GlobalTaintedAdaptorStr, Iplen);
  t_strcpy(GlobalTaintedAdaptorStr, (const char*)Ip);
  return GlobalTaintedAdaptorStr;
}

_TLIB _Unchecked
    static _TPtr<char>
    StaticUncheckedToTStrAdaptor(char* Ip )
{
  int Iplen = strlen(Ip);
  printf("Ip is %s", Ip);
  printf("Iplen is %d", Iplen);
  GlobalTaintedAdaptorStr = string_tainted_malloc(Iplen);
  t_strcpy(GlobalTaintedAdaptorStr, Ip);
  return GlobalTaintedAdaptorStr;
}

_TLIB static _TNt_array_ptr<char> TNtStrMalloc(size_t sz) : count(sz) _Unchecked{
  if(sz >= SIZE_MAX)
    return NULL;
  _TArray_ptr<char> p : count(sz+1) = (_TArray_ptr<char>)t_malloc<char>(sz + 1);
  if (p != NULL)
    p[sz] = 0;
  return _Tainted_Assume_bounds_cast<_TNt_array_ptr<char>>(p, count(sz));
}

_TLIB _Unchecked static _TPtr<char> CheckedToTaintedStrAdaptor(const char* Ip :
                                                               itype(_Nt_array_ptr<const char>))
{
  int Iplen = strlen(Ip);
  _TPtr<char> RetPtr = string_tainted_malloc(Iplen*sizeof(char));
  t_strcpy(RetPtr, (const char*)Ip);
  return RetPtr;
}

_TLIB static _Ptr<char> TaintedToCheckedStrAdaptor(_TPtr<char> Ip)
{
  int Iplen = t_strlen(Ip);
  _Ptr<char> RetPtr = (_Ptr<char>)malloc<char>(Iplen*sizeof(char));
  t_strcpy(RetPtr, Ip);
  return RetPtr;
}
#pragma CHECKED_SCOPE pop
#pragma TLIB_SCOPE pop


#endif // guard 
#endif // TAINTED C
