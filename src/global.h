#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793
#define IPI 0.15915494309

typedef struct Complex {
    double re;
    double im;
} complex;

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct BMPImage {
    FILE *imageFile;
    char *fileName;
    unsigned int width;
    unsigned int height;
    unsigned int extraBits;
    unsigned int fileSize;
    unsigned char *row;
};

struct PPMImage {
    FILE *imageFile;
    char *fileName;
    unsigned int width;
    unsigned int height;
    unsigned char *data;
};

struct Palette {
    struct Color insideColor;
    struct Color avergeColor;
    struct Color *palette;
    unsigned int colors;
};

struct Fractal {
    unsigned int algorithm;
    unsigned int type;
    unsigned int iterations;
    unsigned int kappa;
    unsigned int renderOutside;
    unsigned int renderInside;
    double delta;
    double exponent;
    double rho;
    double radius;
    double zoom;
    complex origin;
    complex constant;
    complex *orbit;
    char julia;
    char fastBreak;
};

static struct Color defaultInside = {0x00, 0x00, 0x00};

static struct Color defaultPalette[] = {
    {0x00, 0xd1, 0x46},
    {0xF6, 0xef, 0x0b},
    {0xf5, 0x32, 0x00},
    {0x31, 0x55, 0xf0}
};

static char defaultFileName [8] = "out.bmp";

static complex O = {.re = 0.0, .im = 0.0};

static struct Color colorRed    = {0xFF, 0x00, 0x00};
static struct Color colorGreen  = {0x00, 0xFF, 0x00};
static struct Color colorBlue   = {0x00, 0x00, 0xFF};
static struct Color colorWhite  = {0xFF, 0xFF, 0xFF};
static struct Color colorBlack  = {0x00, 0x00, 0x00};

double getRandom ();
double sigmoid1 (double);
double sigmoid2 (double);
double sigmoid3 (double);
complex Add (complex, complex);
complex Sub (complex, complex);
complex Mul (complex, complex);
complex Div (complex, complex);
complex Con (complex);
complex RealExp (complex, double);
double NormSq (complex);
double Norm (complex);
void Print (complex);

static unsigned int primes[] = {2, 3, 5,  7, 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 , 67,
71  ,  73 ,  79 ,  83 ,  89 ,  97 , 101 , 103 , 107 , 109 , 113 , 127 , 131 , 137 , 139 , 149 , 151 , 157 , 163,
167 , 173 , 179 , 181 , 191 , 193 , 197 , 199 , 211 , 223 , 227 , 229 , 233 , 239 , 241 , 251 , 257 , 263 , 269,
271 , 277 , 281 , 283 , 293 , 307 , 311 , 313 , 317 , 331 , 337 , 347 , 349 , 353 , 359 , 367 , 373 , 379 , 383,
389 , 397 , 401 , 409 , 419 , 421 , 431 , 433 , 439 , 443 , 449 , 457 , 461 , 463 , 467 , 479 , 487 , 491 , 499};

#endif