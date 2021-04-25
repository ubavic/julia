#include "image.h"
#include "inverse_iteration.h"
#include "global.h"
#include "color.h"

extern struct BMPImage outputImage;
extern struct Palette mainPalette;
extern struct Fractal fractal;

char *plane;
int exponent;

complex ReturnInverseImage (complex w, int i)
{
    complex inverseImage;

    w.re = w.re - fractal.constant.re;
    w.im = w.im - fractal.constant.im;

    double angle = atan2(w.im, w.re)/fractal.exponent;
    double radius = pow(w.re * w.re + w.im * w.im, 1/(2*fractal.exponent));

    inverseImage.re = radius*cos(angle + i*2*PI/fractal.exponent);
    inverseImage.im = radius*sin(angle + i*2*PI/fractal.exponent);

    return inverseImage;
}

void InverseIterate (complex z, int iteration)
{
    int pixel;

    if (iteration >= fractal.iterations){
        pixel = GetPixelFromPoint(z);
        if (pixel == -1)
            return;
        
        plane[pixel] = iteration;
        return;
    }

   complex w;

   for (int i = 0; i < exponent; i++) {
        w = ReturnInverseImage(z, i);
        pixel = GetPixelFromPoint(w);
        if (pixel == -1)
            return;

        if (plane[pixel] == 0){
            plane[pixel] = iteration;
            InverseIterate(w, ++iteration);
        } else {
            plane[pixel] = plane[pixel] > iteration ? plane[pixel] : iteration; 
            InverseIterate(w, iteration+10);
        }
   }
}

int DrawInverseIteration ()
{
    complex z;
    unsigned int i, x, y;
    struct Color color;

    exponent = ceil(fractal.exponent);

    if (fractal.kappa == 0)
        fractal.kappa = 10;

    plane = (char *) malloc(outputImage.height*outputImage.width);
    if (plane == NULL){
        perror("The following error occurred:");
        return 1;
    }

    for (int i = 0; i < outputImage.height*outputImage.width; ++i)
        plane[i] = 0x00;

   
    for (int i = 0; i < fractal.kappa; ++i) {
        z.re = -2+4*getRandom();
        z.im = -2+4*getRandom();
        InverseIterate(z, 0);
    }
    
    for (y = 0; y < outputImage.height; y++){
        for (x = 0; x < 3 * outputImage.width; x+=3){
            if (plane[y*outputImage.width + x/3] > fractal.iterations/2)
                color = mainPalette.insideColor;
            else
                color = mainPalette.palette[0];

            outputImage.row[x] = color.b;
            outputImage.row[x+1] = color.g;
            outputImage.row[x+2] = color.r;
        }

        WriteRowToBMPImage(&outputImage);
    }

    free(plane);
    return 0;
}