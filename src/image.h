#ifndef IMAGE_H
#define IMAGE_H

#include "global.h"

int OpenBMPImage(struct BMPImage*);

void WriteRowToBMPImage(struct BMPImage*);

int CloseBMPImage(struct BMPImage*);

int LoadPPMImage(struct PPMImage*);

int GetPixelFromPoint(complex);

#endif
