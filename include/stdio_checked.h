//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in stdio.h that                //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
//                                                                     //
// TODO: Better Support for _FORTIFY_SOURCE > 0                        //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <stdio.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __STDIO_CHECKED_H
#define __STDIO_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

#if defined(_WIN32) || defined(_WIN64)
// stdin, stdout, and stderr only have to be expressions that have
// type FILE *.  On Windows, they are function calls, so we need to change
// the return type of the function being called.
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned) : itype(_Ptr<FILE>);
#else
extern FILE *stdin : itype(_Ptr<FILE>);
extern FILE *stdout : itype(_Ptr<FILE>);
extern FILE *stderr : itype(_Ptr<FILE>);
#endif

int remove(const char *name : itype(_Nt_array_ptr<const char>));
int rename(const char *from : itype(_Nt_array_ptr<const char>),
           const char *to : itype(_Nt_array_ptr<const char>));
_TLIB FILE *tmpfile(void) : itype(_Ptr<FILE>);
char *tmpnam(char *source : itype(_Nt_array_ptr<char>)) : itype(_Nt_array_ptr<char>);
_TLIB int fclose(FILE *stream : itype(_Ptr<FILE>));
_TLIB int fflush(FILE *stream : itype(_Ptr<FILE>));
_TLIB FILE *fopen(const char * restrict filename : itype(restrict _Nt_array_ptr<const char>),
            const char * restrict mode : itype(restrict _Nt_array_ptr<const char>)) : itype(_Ptr<FILE>);
_TLIB FILE *freopen(const char * restrict filename : itype(restrict _Nt_array_ptr<const char>),
              const char * restrict mode : itype(restrict _Nt_array_ptr<const char>),
              FILE * restrict stream : itype(restrict _Ptr<FILE>)) :
  itype(_Ptr<FILE>);

_TLIB void setbuf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            char * restrict buf : count(BUFSIZ));
_TLIB int setvbuf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            char * restrict buf : count(size),
            int mode, size_t size);

//
// TODO: printing and scanning functions are still mostly
// unchecked because of the use of varargs.
// * There may not be enough arguments for the format string.
// * Any pointer arguments may not meet the requirements of the
//  format string.
//

// We wrap each definition in a complex conditional, there two boolean values:
// - we are fortifying, or we're not (_FORTIFY_SOURCE==0 is not fortifying)
// - there is or there isn't a macro hash-defining this symbol (defined(symbol))
// Cases:
// - Fortifying,     Macro Exists: this is expected, we don't need the definition
// - Not Fortifying, Macro Exists: we need the definition, we need to undef macro
// - Fortifying,     No Macro:     we need the definition
// - Not Fortifying, No Macro:     we need the definition


#if _FORTIFY_SOURCE == 0 || !defined(fprintf)
#undef fprintf
_TLIB _Unchecked
int fprintf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);
#endif

_TLIB _Unchecked
int fscanf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
           const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);

#if _FORTIFY_SOURCE == 0 || !defined(printf)
#undef printf
_Unchecked
int printf(const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);
#endif

_Unchecked
int scanf(const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);

#if _FORTIFY_SOURCE == 0 || !defined(sprintf)
#undef sprintf
// The output buffer parameter s is an unchecked pointer because no bounds are provided.
_Unchecked
int sprintf(char * restrict s,
            const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);
#endif

_Unchecked
int sscanf(const char * restrict s : itype(restrict _Nt_array_ptr<const char>),
           const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);

#if _FORTIFY_SOURCE == 0 || !defined(snprintf)
#undef snprintf

// Since snprintf automatically adds the null terminator
// and counts that number in n, s only needs count(n-1) per the 
// definition of _Nt types. Additional declaration for arrays 
// available in checkedc_extensions.h

_Unchecked
int snprintf(char * restrict s : itype(restrict _Nt_array_ptr<char>) count(n-1),
             size_t n _Where n > 0,
             const char * restrict format : itype(restrict _Nt_array_ptr<const char>), ...);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(vfprintf)
#undef vfprintf
_TLIB _Unchecked
int vfprintf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
             const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
             va_list arg);
#endif

_TLIB _Unchecked
int vfscanf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
            va_list arg);

#if _FORTIFY_SOURCE == 0 || !defined(vprintf)
#undef vprintf
_Unchecked
int vprintf(const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
             va_list arg);
#endif

_Unchecked
int vscanf(const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
            va_list arg);

#if _FORTIFY_SOURCE == 0 || !defined(vsnprintf)
#undef vsnprintf
_Unchecked
int vsnprintf(char * restrict s : count(n), size_t n,
              const char * restrict format,
              va_list arg);
#endif

#if _FORTIFY_SOURCE == 0 || !defined(vsprintf)
#undef vsprintf
// The output buffer parameter has an unchecked pointer type becuse it is missing bounds.
_Unchecked
int vsprintf(char * restrict s,
             const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
             va_list arg);
#endif

_Unchecked
int vsscanf(const char * restrict s : itype(restrict _Nt_array_ptr<const char>),
            const char * restrict format : itype(restrict _Nt_array_ptr<const char>),
            va_list arg);

_TLIB int fgetc(FILE *stream : itype(_Ptr<FILE>));
_TLIB int fputc(int c, FILE *stream : itype(_Ptr<FILE>));
_TLIB char *fgets(char * restrict s : count(n), int n,
            FILE * restrict stream : itype(restrict _Ptr<FILE>)) :
  bounds(s, s + n);
_TLIB int fputs(const char * restrict s : itype(restrict _Nt_array_ptr<const char>),
          FILE * restrict stream : itype(restrict _Ptr<FILE>));
_TLIB int getc(FILE *stream : itype(_Ptr<FILE>));
_TLIB int putc(int c, FILE *stream : itype(_Ptr<FILE>));
_TLIB int puts(const char *str : itype(_Nt_array_ptr<const char>));
_TLIB int ungetc(int c, FILE *stream : itype(_Ptr<FILE>));

_TLIB size_t fread(void * restrict pointer : byte_count(size * nmemb),
             size_t size, size_t nmemb,
             FILE * restrict stream : itype(restrict _Ptr<FILE>));

_TLIB size_t fwrite(const void * restrict pointer : byte_count(size * nmemb),
              size_t size, size_t nmemb,
              FILE * restrict stream : itype(restrict _Ptr<FILE>));

_TLIB int fgetpos(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            fpos_t * restrict pos : itype(restrict _Ptr<fpos_t>));

_TLIB int fseek(FILE *stream : itype(_Ptr<FILE>), long int offset, int whence);
_TLIB int fsetpos(FILE *stream : itype(_Ptr<FILE>),
            const fpos_t *pos :  itype(_Ptr<const fpos_t>));

_TLIB long int ftell(FILE *stream : itype(_Ptr<FILE>));
_TLIB void rewind(FILE *stream : itype(_Ptr<FILE>));

_TLIB void clearerr(FILE *stream : itype(_Ptr<FILE>));
_TLIB int feof(FILE *stream : itype(_Ptr<FILE>));
_TLIB int ferror(FILE *stream : itype(_Ptr<FILE>));
void perror(const char *s : itype(_Nt_array_ptr<const char>));

#include "_builtin_stdio_checked.h"

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C
