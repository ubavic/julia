#include "image.h"
#include "budhabrot.h"
#include "escape_time.h"
#include "global.h"
#include "color.h"

extern struct BMPImage outputImage;
extern struct Fractal fractal;

unsigned int findCycle (unsigned int iterations)
{
    for (int i = iterations-2; i > 0; i--){
        if (fabs(fractal.orbit[iterations - 1].im - fractal.orbit[i].im) < 10e-2 &&  fabs(fractal.orbit[iterations - 1].re - fractal.orbit[i].re) < 10e-2){
            return i;
        }
    }

    return 0;
}

int DrawBudhabrot ()
{
    complex z, w;
    unsigned int i, x, y, point;

    complex (*FractalAlgorithm)(complex, complex);
    switch (fractal.type){
        case 0:
            FractalAlgorithm = &Mandelbrot;
            break;
        case 1:
            FractalAlgorithm = &Multibrot;
            break;
        case 2:
            FractalAlgorithm = &Mandelbar;
            break;
        case 3:
            FractalAlgorithm = &Ship;
            break;
    }

    if (fractal.kappa == 0)
        fractal.kappa = 100000;

    unsigned int *plane = (unsigned int *) malloc(outputImage.height*outputImage.width*sizeof(unsigned int));
    if (plane == NULL){
        perror("The following error occurred:");
        return 1;
    }

    for (int i = 0; i < outputImage.height*outputImage.width; ++i)
        plane[i] = 0x00;

    fractal.orbit = (complex *) malloc(fractal.iterations*sizeof(complex));
    if (fractal.orbit == NULL){
        perror("The following error occurred:");
        return 1;
    }

    // double =  bigRadius = 2*pow(2, 1/(fractal.exponent-1));

    for (point = 0; point < fractal.kappa; point++) {
        z.re = -2+4*getRandom();
        z.im = -2+4*getRandom();
        fractal.orbit[0] = z;

        for (i = 1; i < fractal.iterations; i++){
            fractal.orbit[i] = FractalAlgorithm (z, fractal.orbit[i-1]);
            fractal.rho = NormSq(fractal.orbit[i]);
            if (fractal.rho > fractal.radius)
                break;
        }

        if (i < fractal.iterations - 5) {
            for (y = 0; y < i; y++){
                x = GetPixelFromPoint(fractal.orbit[y]);
                if (x != -1)
                        plane[x]++;
            }
        }
    }
    
    int max = 1;
    for (int i = 0; i < outputImage.height*outputImage.width; ++i)
        max = max > plane[i] ? max : plane[i];

    printf("%d\n", max);

    for (y = 0; y < outputImage.height; y++){
        for (x = 0; x < outputImage.width; x++){
            outputImage.row[3*x] =     0xFF*plane[y*outputImage.width+x]/max;
            outputImage.row[3*x + 1] = 0xFF*plane[y*outputImage.width+x]/max;
            outputImage.row[3*x + 2] = 0xFF*plane[y*outputImage.width+x]/max;
        }
        WriteRowToBMPImage(&outputImage);
    }

    free(plane);
    return 0;
}