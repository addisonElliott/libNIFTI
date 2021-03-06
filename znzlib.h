#ifndef _ZNZLIB_H_
#define _ZNZLIB_H_

/*
znzlib.h  (zipped or non-zipped library)

*****            This code is released to the public domain.            *****

*****  Author: Mark Jenkinson, FMRIB Centre, University of Oxford       *****
*****  Date:   September 2004                                           *****

*****  Neither the FMRIB Centre, the University of Oxford, nor any of   *****
*****  its employees imply any warranty of usefulness of this software  *****
*****  for any purpose, and do not assume any liability for damages,    *****
*****  incidental or otherwise, caused by any use of this document.     *****

*/

/*

This library provides an interface to both compressed (gzip/zlib) and
uncompressed (normal) file IO.  The functions are written to have the
same interface as the standard file IO functions.  

To use this library instead of normal file IO, the following changes
are required:
 - replace all instances of FILE* with znzFile
 - change the name of all function calls, replacing the initial character
   f with the znz  (e.g. fseek becomes znzseek)
 - add a third parameter to all calls to znzopen (previously fopen)
   that specifies whether to use compression (1) or not (0)
 - use znz_isnull rather than any (pointer == NULL) comparisons in the code
 
NB: seeks for writable files with compression are quite restricted

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "libnifti_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/* include optional check for HAVE_FDOPEN here, from deleted config.h:

   uncomment the following line if fdopen() exists for your compiler and
   compiler options
*/
/* #define HAVE_FDOPEN */


#ifdef HAVE_ZLIB
#if defined(ITKZLIB)
#include "itk_zlib.h"
#else
#include "zlib.h"
#endif
#endif


LIBNIFTI_EXPORT struct znzptr {
  int withz;
  FILE* nzfptr;
#ifdef HAVE_ZLIB
  gzFile zfptr;
#endif
} ;

/* the type for all file pointers */
typedef LIBNIFTI_EXPORT struct znzptr * znzFile;


/* int znz_isnull(znzFile f); */
/* int znzclose(znzFile f); */
#define znz_isnull(f) ((f) == NULL)
#define znzclose(f)   Xznzclose(&(f))

/* Note extra argument (use_compression) where 
   use_compression==0 is no compression
   use_compression!=0 uses zlib (gzip) compression
*/

LIBNIFTI_EXPORT znzFile znzopen(const char *path, const char *mode, int use_compression);

LIBNIFTI_EXPORT znzFile znzdopen(int fd, const char *mode, int use_compression);

LIBNIFTI_EXPORT int Xznzclose(znzFile * file);

LIBNIFTI_EXPORT size_t znzread(void* buf, size_t size, size_t nmemb, znzFile file);

LIBNIFTI_EXPORT size_t znzwrite(const void* buf, size_t size, size_t nmemb, znzFile file);

LIBNIFTI_EXPORT long znzseek(znzFile file, long offset, int whence);

LIBNIFTI_EXPORT int znzrewind(znzFile stream);

LIBNIFTI_EXPORT long znztell(znzFile file);

LIBNIFTI_EXPORT int znzputs(const char *str, znzFile file);

LIBNIFTI_EXPORT char * znzgets(char* str, int size, znzFile file);

LIBNIFTI_EXPORT int znzputc(int c, znzFile file);

LIBNIFTI_EXPORT int znzgetc(znzFile file);

#if !defined(WIN32)
LIBNIFTI_EXPORT int znzprintf(znzFile stream, const char *format, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif
