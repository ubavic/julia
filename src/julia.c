#include "image.h"
#include "parse_options.h"
#include "inverse_iteration.h"
#include "escape_time.h"
#include "budhabrot.h"

int SetImageFractal();
void SetDefaults();

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

    if (OpenImage (&outputImage))
        return 1;

    if (outputImage.algorithm == 0)
        DrawEscapeTime ();
    else if (outputImage.algorithm == 1)
        DrawInverseIteration ();
    else if (outputImage.algorithm == 2)
        DrawBudhabrot ();

    if (CloseImage (&outputImage))
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

    printf (", with algorithm (%d).\n", outputImage.algorithm);
    printf ("Coloring: %d:%d.\n", outputImage.renderOutside, outputImage.renderInside);
    printf ("Max. iterations: %d;\n", fractal.iterations);
    printf ("Center is at %f + %fi, and zoom factor is %f.\n", fractal.origin.re, fractal.origin.im, outputImage.zoom);
    printf ("Saving to %dpx by %dpx image \"%s\".\n", outputImage.width, outputImage.height, outputImage.fileName);

    outputImage.zoom = 2 / outputImage.zoom;

    if (outputImage.width >= outputImage.height){
        fractal.origin.im -= outputImage.zoom;
        outputImage.zoom+=outputImage.zoom;
        outputImage.delta=outputImage.zoom/outputImage.height;
        fractal.origin.re = fractal.origin.re - (outputImage.delta * outputImage.width) / 2;
    } else {
        fractal.origin.re -= outputImage.zoom;
        outputImage.zoom+=outputImage.zoom;
        outputImage.delta=outputImage.zoom/outputImage.width;
        fractal.origin.im = fractal.origin.im - (outputImage.delta * outputImage.height) / 2;
    }

    return 0;
}

void SetDefaults ()
{
    outputImage.width = 1000;
    outputImage.height = 1000;
    outputImage.zoom = 1.0;
    outputImage.renderOutside = 0;
    outputImage.renderInside = 0;
    outputImage.fileName = &defaultFileName[0];
    outputImage.algorithm = 0;
    outputImage.row = NULL;
    outputImage.imageFile = NULL;

    mainPalette.palette = defaultPalette;
    mainPalette.colors = 4;
    mainPalette.insideColor = defaultInside;
    
    fractal.type = 0;
    fractal.iterations = 200;
    fractal.kappa = 0; 
    fractal.exponent = 2.0; 
    fractal.julia = 0;
    fractal.radius = 4.0;
    fractal.fastBreak = 1;
}
