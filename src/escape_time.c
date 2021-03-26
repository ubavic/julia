#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "color.h"
#include "escape_time.h"

extern struct Image outputImage;
extern struct Image inputImage;
extern struct Fractal fractal;

int DrawEscapeTime ()
{

	fractal.orbit = (complex *) malloc(fractal.iterations*sizeof(complex));
    if (fractal.orbit == NULL){
        perror("The following error occurred:");
        return 1;
    }

	complex (*FractalAlgorithm)(complex, complex);
	void (*GetOutsideColor)(unsigned int, struct Color *);
	void (*GetInsideColor)(unsigned int, struct Color *);

	switch(outputImage.renderOutside){
		case 0:
			GetOutsideColor = &GetOutside;
			break;
		case 1:
			GetOutsideColor = &ClassicColor;
			break;
		case 2:
			GetOutsideColor = &ContinuousColor;
			break;
		case 3:
			GetOutsideColor = &SmoothColor;
			break;
		case 4:
			fractal.fastBreak = 0;
			GetOutsideColor = &ArgumentColor;
			if (fractal.kappa == 0)
        		fractal.kappa = 5;
			break;
		case 5:
			fractal.fastBreak = 0;
			GetOutsideColor = &ContinuousArgumentColor;
			if (fractal.kappa == 0)
        		fractal.kappa = 5;
			break;
		case 6:
			GetOutsideColor = &GridColor;
			break;
		case 7:
			if (inputImage.imageFile != NULL) {
				GetOutsideColor = &GridImage;
			} else {
				printf("Image is not loaded. Using default outside coloring.\n");
				GetOutsideColor = &GetOutside;
			}
			break;
		case 8:
			GetOutsideColor = &DistanceColor;
			if (fractal.kappa == 0)
        		fractal.kappa = 100;
			break;
		case 9:
			GetOutsideColor = &GreenColor;
			break;
		case 10:
			GetOutsideColor = &BotcherCoordinatesColor;
			break;
		case 11:
			if (inputImage.imageFile != NULL) {
				GetOutsideColor = &BotcherImageColor;
			} else {
				printf("Image is not loaded. Using default outside coloring.\n");
				GetOutsideColor = &GetOutside;
			}
			break;	
	}

	switch(outputImage.renderInside){
		case 0:
			GetInsideColor = &GetInside;
			break;
		case 1:
			GetInsideColor = &DiskRainbowColor;
			break;
		case 2:
			if (inputImage.imageFile != NULL) {
				GetInsideColor = &InsideImage;
			} else {
				printf("Image is not loaded. Using default outside coloring.\n");
				GetInsideColor = &GetInside;
			}
			break;
		case 3:
			GetInsideColor = &SpeedColor;
			break;
		case 4:
			GetInsideColor = &ArgumentColor;
			if (fractal.kappa == 0)
        		fractal.kappa = 5;
			break;
		case 5:
			GetInsideColor = &ContinuousArgumentColor;
			if (fractal.kappa == 0)
        		fractal.kappa = 5;
			break;
	}

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

	complex z;
	unsigned int i, x, y;
	z.im = fractal.origin.im;
	struct Color color;

	for (y = 0; y < outputImage.height; y++){
		z.re = fractal.origin.re;

		for (x = 0; x < 3 * outputImage.width; x+=3){
			fractal.orbit[0] = z;

			for (i = 1; i < fractal.iterations; i++){
				if (fractal.julia)
					fractal.orbit[i] = FractalAlgorithm (fractal.constant, fractal.orbit[i-1]);
				else
				 	fractal.orbit[i] = FractalAlgorithm (z, fractal.orbit[i-1]);

				fractal.rho = NormSq(fractal.orbit[i]);

				if (fractal.fastBreak && fractal.rho > fractal.radius)
					break;
			}

			if (fractal.rho < fractal.radius)
				GetInsideColor (i, &color);
			else
				GetOutsideColor (i, &color);

			outputImage.row[x] = color.b;
			outputImage.row[x+1] = color.g;
			outputImage.row[x+2] = color.r;

			z.re+=outputImage.delta;
		}

		WriteRow(&outputImage);
		z.im+=outputImage.delta;
	}

	return 0;
}

complex Mandelbrot (complex z, complex w)
{
	double tmp = w.re*w.re - w.im*w.im + z.re;
	w.im = 2*w.re*w.im + z.im;
	w.re = tmp;
	return w;
}

complex Multibrot (complex z, complex w)
{
	double tmp1, tmp2;
	tmp1 = w.re * w.re + w.im * w.im;
	tmp1 = pow(tmp1, fractal.exponent/2);
	tmp2 = atan2(w.im, w.re);
	tmp2 = tmp2 * fractal.exponent;
	w.re = tmp1 * cos(tmp2) + z.re;
	w.im = tmp1 * sin(tmp2) + z.im;
	return w;
}

complex Mandelbar (complex z, complex w)
{
	double tmp = w.re * w.re - w.im * w.im + z.re;
	w.im = -2 * w.re * w.im + z.im;
	w.re = tmp;
	return w;
}

complex Ship (complex z, complex w)
{
	w.re = fabs(w.re);
	w.im = fabs(w.im);
	double tmp = w.re * w.re - w.im * w.im + z.re;
	w.im = 2 * w.re * w.im + z.im;
	w.re = tmp;
	return w;
}
