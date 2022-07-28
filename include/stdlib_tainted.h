//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in stdlib.h that               //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
/////////////////////////////////////////////////////////////////////////

//will later change this to tainted -c
#ifdef __checkedc
#ifndef __STDLIB_TAINTED_H
#define __STDLIB_TAINTED_H

#pragma TLIB_SCOPE push
#pragma TLIB_SCOPE on

#include <stddef.h>
_Mirror static void* c_malloc(size_t size);
_Mirror static void* c_realloc(_TArray_ptr<void> pointer, size_t size);
_Mirror static void c_free(_TArray_ptr<void>pointer);
_Mirror static int c_isTaintedPointerToTaintedMem(_TArray_ptr<void> pointer);
_Mirror static int c_isPointerToTaintedMem(void* pointer);
_Mirror static void* c_fetch_sandbox_address();
_Mirror static unsigned int c_fetch_pointer_offset(_TArray_ptr<void> pointer_name);
_Mirror static unsigned int c_fetch_pointer_from_offset(unsigned long pointer_offset);
_Mirror static unsigned long c_fetch_sandbox_heap_address();

// TODO: express alignment constraints once where clauses have been added.
_Itype_for_any(T) _TArray_ptr<T> t_malloc(size_t size);

_Itype_for_any(T) void t_free(_TArray_ptr<T> pointer);

_Itype_for_any(T) _TArray_ptr<T> t_realloc(_TArray_ptr<T> pointer, size_t size);

/* Convert a string to a floating-point number.  */
extern double t_strtod (_TNt_array_ptr<char> __restrict __nptr,
                       _TPtr<_TPtr<char>>__restrict __endptr);
#pragma TLIB_SCOPE pop
#endif  // guard
#endif  // Tainted C
