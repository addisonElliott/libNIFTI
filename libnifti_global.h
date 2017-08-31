#ifndef LIBNIFTI_GLOBAL_H
#define LIBNIFTI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIBNIFTIC_STATIC
#  define LIBNIFTI_EXPORT
#else // LIBNIFTI_STATIC
#  if defined(LIBNIFTI_LIBRARY)
#     define LIBNIFTI_EXPORT Q_DECL_EXPORT
#  else
#     define LIBNIFTI_EXPORT Q_DECL_IMPORT
#  endif
#endif // LIBNIFTI_STATIC

#ifdef __GNUC__
#  define UNUSED __attribute__((__unused__))
#else
#  define UNUSED
#endif

#endif // LIBNIFTI_GLOBAL_H
