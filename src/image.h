#ifndef IMAGE_H
#define IMAGE_H

#include "global.h"

int OpenImage (struct Image*);

void WriteRow (struct Image*);

int CloseImage (struct Image*);

int LoadPPMImage (struct PPMImage*);

int GetPixelFromPoint (complex);

#endif
