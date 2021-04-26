#include <stdlib.h>
#include <string.h>
#include "parse_options.h"
#include "image.h"
#include "global.h"
#include "color.h"

extern struct BMPImage outputImage;
extern struct PPMImage inputImage;
extern struct Fractal fractal;

int Parse(int argc, char** argv)
{
    int c, option_index;
    char strBuffer[512];

    strBuffer[0] = 0x00;

    while (1) {
        c = getopt_long(argc, argv, "a:b:c:d:e:f:hi:j:k:l:o:p:r:z:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;

                printf("option %s", long_options[option_index].name);

                if (optarg)
                    printf(" with arg %s", optarg);

                printf("\n");
                break;
            case 'a':
                sscanf(optarg, "%u", &fractal.algorithm);
                if (fractal.type > 2) {
                    strcat(strBuffer, "Algorithm can be 0, 1 or 2. Using default value (0).\n");
                    fractal.type = 0;
                }
                break;
            case 'b':
                sscanf(optarg, "%lf", &fractal.radius);
                break;
            case 'c':
                sscanf(optarg, "%lf:%lf", &fractal.origin.re, &fractal.origin.im);
                break;
            case 'd':
                sscanf(optarg, "%u:%u", &outputImage.width, &outputImage.height);
                break;
            case 'e':
                sscanf(optarg, "%lf", &fractal.exponent);
                break;
            case 'f':
                sscanf(optarg, "%u", &fractal.type);
                if (fractal.type > 3) {
                    strcat(strBuffer, "Fractal number can be 0, 1, 2 or 3. Using default value (1).\n");
                    fractal.type = 1;
                }
                break;
            case 'h':
                printf(HELPMSG);
                return 2;
                break;
            case 'i':
                sscanf(optarg, "%u", &fractal.iterations);
                break;
            case 'j':
                fractal.julia = 1;
                sscanf(optarg, "%lf:%lf", &fractal.constant.re, &fractal.constant.im);
                break;
            case 'k':
                sscanf(optarg, "%u", &fractal.kappa);
                break;
            case 'l':
                inputImage.fileName = malloc(20 * sizeof(char));
                sscanf(optarg, "%s", inputImage.fileName);
                if (LoadPPMImage(&inputImage)) {
                    printf("Can't load PPM image\n");
                    return 1;
                }
                break;
            case 'o':
                sscanf(optarg, "%s", outputImage.fileName);
                break;
            case 'p':
                if (LoadPalete(optarg))
                    return 1;
                break;
            case 'r':
                sscanf(optarg, "%u:%u", &fractal.renderOutside, &fractal.renderInside);
                if (fractal.renderOutside > 11) {
                    strcat(strBuffer, "Outside render number can be from 0 to 7. Using the default value (1).\n");
                    fractal.renderOutside = 1;
                }
                if (fractal.renderInside > 5) {
                    strcat(strBuffer, "Inside render number can be 0 to 5. Using the default value (1).\n");
                    fractal.renderOutside = 1;
                }
                break;
            case 'z':
                sscanf(optarg, "%lf", &fractal.zoom);
                if (fractal.zoom < 0) {
                    strcat(strBuffer, "The zoom factor must be bigger than 0. Using the default value (1).\n");
                    fractal.zoom = 1.0;
                }
                break;
            default:
                break;
        }
    }

    if (optind < argc) {
        printf("Invalid options: ");

        while (optind < argc)
            printf("%s ", argv[optind++]);

        printf("Type mandelbrot --help for usage.\n");
        return 1;
    }

    printf("%s", strBuffer);

    return 0;
}
