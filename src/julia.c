#include "image.h"
#include "parse_options.h"
#include "inverse_iteration.h"
#include "escape_time.h"
#include "budhabrot.h"

int SetImageFractal();
void SetDefaults();

extern struct BMPImage outputImage;
extern struct Palette mainPalette;
extern struct Fractal fractal;

int main (int argc, char** argv)
{
    SetDefaults ();

    switch (Parse (argc, argv)){
	case 1:
		return 1;
	case 2:
		return 0;
    }

    if (SetImageFractal ())
        return 1;

    if (OpenBMPImage (&outputImage))
        return 1;

    if (fractal.algorithm == 0)
        DrawEscapeTime ();
    else if (fractal.algorithm == 1)
        DrawInverseIteration ();
    else if (fractal.algorithm == 2)
        DrawBudhabrot ();

    if (CloseBMPImage (&outputImage))
        return 1;

    printf ("Done!\n");

    return 0;
}


int SetImageFractal ()
{
    printf ("Calculating ");

    if(fractal.julia)
        printf ("Julia set of ");

    if (fractal.type == 0)
        printf ("Mandelbrot set");
    else if (fractal.type == 1)
        printf ("Multibrot set (exponent = %f)", fractal.exponent);
    else if (fractal.type == 2)
        printf ("Mandelbar set");
    else if (fractal.type == 3)
        printf ("Burning ship");

    printf (", with algorithm (%d).\n", fractal.algorithm);
    printf ("Coloring: %d:%d.\n", fractal.renderOutside, fractal.renderInside);
    printf ("Max. iterations: %d;\n", fractal.iterations);
    printf ("Center is at %f + %fi, and zoom factor is %f.\n", fractal.origin.re, fractal.origin.im, fractal.zoom);
    printf ("Saving to %dpx by %dpx image \"%s\".\n", outputImage.width, outputImage.height, outputImage.fileName);

    fractal.zoom = 2 / fractal.zoom;

    if (outputImage.width >= outputImage.height){
        fractal.origin.im -= fractal.zoom;
        fractal.zoom+=fractal.zoom;
        fractal.delta=fractal.zoom/outputImage.height;
        fractal.origin.re = fractal.origin.re - (fractal.delta * outputImage.width) / 2;
    } else {
        fractal.origin.re -= fractal.zoom;
        fractal.zoom+=fractal.zoom;
        fractal.delta=fractal.zoom/outputImage.width;
        fractal.origin.im = fractal.origin.im - (fractal.delta * outputImage.height) / 2;
    }

    return 0;
}

void SetDefaults ()
{
    outputImage.width = 1000;
    outputImage.height = 1000;
    outputImage.fileName = &defaultFileName[0];

    outputImage.row = NULL;
    outputImage.imageFile = NULL;

    mainPalette.palette = defaultPalette;
    mainPalette.colors = 4;
    mainPalette.insideColor = defaultInside;
    
    fractal.algorithm = 0;
    fractal.type = 0;
    fractal.iterations = 200;
    fractal.kappa = 0; 
    fractal.exponent = 2.0; 
    fractal.julia = 0;
    fractal.radius = 4.0;
    fractal.fastBreak = 1;
    fractal.zoom = 1.0;
    fractal.renderOutside = 0;
    fractal.renderInside = 0;
}
