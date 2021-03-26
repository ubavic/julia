#ifndef PARSE_OPTIONS_H
#define PARSE_OPTIONS_H

#include <getopt.h>

#define HELPMSG "Usage: julia [OPTIONS]\n"\
				"  -a, --algorithm=ALGORITHM      choose drawing algorithm \n"\
                "  -b, --bailout=BAILOUT          set bailout radius to BAILOUT\n"\
                "  -c, --center=POINT             set center of the image to POINT\n"\
                "  -d, --dimensions=DIMENSIONS    set dimensions of the image to DIMENSIONS\n"\
                "  -e, --exponent=EXPONENT        set exponent for computing multibrot\n"\
                "  -f, --fractal=FRACTAL          set fractal\n"\
                "  -h, --help                     print this message \n"\
                "  -i, --iterations=ITERATIONS    set the iteration number used for calculating sets\n"\
                "  -j, --julia=JULIA_CONST        render Julia fractal with JULIA_CONST as parameter\n"\
                "  -k, --kappa=KAPPA              set KAPPA parameter\n"\
                "  -l, --load=PATHNAME            load PPM image from PATHNAME\n"\
                "  -o, --output=PATHNAME          set output image path to PATHNAME\n"\
                "  -p, --palette=PATHNAME         loads palette from PATHNAME\n"\
                "  -r, --render=OUTSIDE:INSIDE    set rendering technique to INSIDE and OUTSIDE;\n"\
                "  -z, --zoom=ZOOM                set zoom factor to ZOOM\n"\
                "\n"\
                "POINT and JULIA_CONST should be given in format REAL:IMAGINARY, where REAL and IMAGINARY are doubles\n"\
                "DIMENSIONS should be given in format WIDTH:HEIGHT, where WIDTH and HEIGHT are unsigned integers\n"\
                "EXPONENT should be double, and ZOOM should be positive double\n"\
                "\nFRACTAL can be one of the following numbers:\n"\
                "  0 - Mandelbrot (default)\n"\
                "  1 - Multibrot\n"\
                "  2 - Mandelbar\n"\
                "  3 - Burning ship\n"\
                "\nOUTSIDE can be one of the following numbers:\n"\
                "  0 - Plain coloring (default)\n"\
                "  1 - Classic coloring\n"\
                "  2 - Continuous coloring\n"\
                "  3 - Smooth coloring\n"\
                "  4 - Argument coloring\n"\
                "  5 - Continuous argument coloring \n"\
                "  6 - Grid coloring\n"\
                "  7 - Grid image\n"\
                "\nINSIDE can be one of the following numbers:\n"\
                "  0 - Plain coloring (default)\n"\
                "  1 - Rainbow disk coloring\n"\
                "  2 - Inside image coloring\n"\
                "  3 - Convergence speed coloring\n"\
                "  4 - Argument coloring\n"\
                "  5 - Continuous argument coloring \n"\
                "\nALGORITHM can be one of the following numbers:\n"\
                "  0 - Escape-time algorithm (default)\n"\
                "  1 - Inverse iteration algorithm\n"\
                "  2 - Budhabrot algorithm\n"\
                "\nKAPPA should be an unsigned integer. It is used as a parameter for different algorithms:\n"\
                "  - if Argument, Continuous argument, Rainbow disk or Inside image coloring is used, \n"\
                "    KAPPA will determine which iteration is used for coloring;\n"\
                "  - if Budhabrot or Inverse iteration algorithm is used,\n"\
                "    KAPPA will determine the number of random points used for drawing.\n"\
                "\n"\
                "Example:\n"\
                "./julia -f 0 -c 0.2:-0.5 -d 2000:2000 -z 3.0 -r 2 -p palette2\n"

static struct option long_options[] ={
		{"algorithm",   required_argument,  0,      'a'},
        {"bailout",     required_argument,  0,      'b'},
        {"center",      required_argument,  0,      'c'},
        {"dimensions",  required_argument,  0,      'd'},
        {"exponent",    required_argument,  0,      'e'},
        {"fractal",     required_argument,  0,      'f'},
        {"help",        no_argument,        0,      'h'},
        {"iterations",  required_argument,  0,      'i'},
        {"julia",       required_argument,  0,      'j'},
        {"kappa",       required_argument,  0,      'k'},
        {"load",        required_argument,  0,      'l'},
        {"output",      required_argument,  0,      'o'},
        {"palette",     required_argument,  0,      'p'},
        {"render",      required_argument,  0,      'r'},
        {"zoom",        required_argument,  0,      'z'},
        {0, 0, 0, 0}
};

int Parse (int, char **);

#endif