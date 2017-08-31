#ifndef LIBNIFTI_H
#define LIBNIFTI_H

#include "libnifti_global.h"
#include "nifti1_io.h"

#include "quazip.h"
#include "quazipfile.h"

// This is a hacky way of adding QuaZip support to the nifticlib library
// In reality, it would be much better to just create a C++ wrapper for nifticlib, or even
// write a NIFTI loader in C++ altogether.

LIBNIFTI_EXPORT nifti_image *nifti_image_read_qt(QuaZip *zip, QString filename, bool readData = true);
LIBNIFTI_EXPORT int nifti_image_load_qt(nifti_image *nim, QuaZipFile &file);

#endif // LIBNIFTI_H
