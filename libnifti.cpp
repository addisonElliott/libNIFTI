#include "libnifti.h"

nifti_image *nifti_image_read_qt(QuaZip *zip, QString filename, bool readData)
{
    // TODO: Probably worthwhile to make a NIFTI C++ wrapper
    // Additionally, there are no checks, it just loads the filename, doesn't check for hdr or anything
    if (!zip->setCurrentFile(filename))
        return NULL;

    QuaZipFile file(zip);
    if (!file.open(QIODevice::ReadOnly))
        return NULL;

    nifti_1_header nhdr;

    long read = file.read((char *)&nhdr, sizeof(nhdr));
    if (read < sizeof(nhdr))
        return NULL;

    nifti_image *niftiImage = nifti_convert_nhdr2nim(nhdr, NULL);
    if (!niftiImage)
        return NULL;

    // TODO: Actually read extensions
    long extensionSize = niftiImage->iname_offset - sizeof(nhdr);
    char buf[1024];
    file.read((char *)&buf, extensionSize);
    niftiImage->num_ext = 0;
    niftiImage->ext_list = NULL;

    if (readData)
    {
        if (nifti_image_load_qt(niftiImage, file) < 0)
        {
            nifti_image_free(niftiImage);
            return NULL;
        }
    }
    else
        niftiImage->data = NULL;

    niftiImage->fname = NULL;
    niftiImage->iname = NULL;

    return niftiImage;
}

int nifti_image_load_qt(nifti_image *nim, QuaZipFile &file)
{
    size_t totalVolumeSize = nifti_get_volsize(nim);

    if (!nim->data)
    {
        nim->data = (void *)calloc(1, totalVolumeSize);
        if (!nim->data)
            return -1;
    }

    size_t read = file.read((char *)nim->data, totalVolumeSize);

    if (read < totalVolumeSize)
        return -1;

    if (nim->swapsize > 1 && nim->byteorder != nifti_short_order())
        nifti_swap_Nbytes(totalVolumeSize / nim->swapsize, nim->swapsize, nim->data);

    return 0;
}

