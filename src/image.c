#include "image.h"
#include "global.h"

extern struct BMPImage outputImage;
extern struct Fractal fractal;

static unsigned char zeros [3] = {0x00, 0x00, 0x00};

unsigned char BMPheader [54] = {
			'B', 'M',
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            54,   0x00, 0x00, 0x00,
            40,   0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 24,   0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x13, 0x0B, 0x00, 0x00,
            0x13, 0x0B, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00 
        };

int OpenBMPImage (struct BMPImage *image)
{
	image->row = (unsigned char*) malloc(3 * image->width * sizeof(unsigned char));

    if (image->row == NULL){
        perror("The following error occurred:");
        return 1;
    }

    for (int i = 0; i < 3 * image->width; ++i)
        image->row[i] = 0x00;

    image->imageFile = fopen(image->fileName, "w+");

    if (image->imageFile == NULL){
        perror("The following error occurred:");
        return 1;
    }

    image->extraBits = 4 - ((image->width * 3) % 4);

    if (image->extraBits == 4)
        image->extraBits = 0;

    image->fileSize = 54 + ((image->width * 3 + image->extraBits) * image->height);

    BMPheader [2]  = (unsigned char)(image->fileSize);
    BMPheader [3]  = (unsigned char)(image->fileSize >> 8);
    BMPheader [4]  = (unsigned char)(image->fileSize >> 16);
    BMPheader [5]  = (unsigned char)(image->fileSize >> 24);
    BMPheader [18] = (unsigned char)(image->width);
    BMPheader [19] = (unsigned char)(image->width >> 8);
    BMPheader [20] = (unsigned char)(image->width >> 16);
    BMPheader [21] = (unsigned char)(image->width >> 24);
    BMPheader [22] = (unsigned char)(image->height);
    BMPheader [23] = (unsigned char)(image->height >> 8);
    BMPheader [24] = (unsigned char)(image->height >> 16);
    BMPheader [25] = (unsigned char)(image->height >> 24);

    fwrite(BMPheader, sizeof(char), 54, image->imageFile);

    return 0;
}

void WriteRowToBMPImage (struct BMPImage *image)
{
    fwrite(image->row, 3 * sizeof(unsigned char), image->width, image->imageFile);

    if (image->extraBits != 0)
        fwrite(zeros, sizeof(unsigned char), image->extraBits, image->imageFile);
}

int CloseBMPImage (struct BMPImage *image)
{
    free(image->row);
    fclose(image->imageFile);

    return 0;
}

int GetPixelFromPoint (complex w)
{
    unsigned int row = floor((w.im - fractal.origin.im)/fractal.delta); 
    unsigned int column = floor((w.re - fractal.origin.re)/fractal.delta);
    if (row >= outputImage.height || row < 0 || column >= outputImage.width || column < 0)
        return -1;
    else
        return row*outputImage.width + column;
}

int LoadPPMImage (struct PPMImage *image)
{
    unsigned char* string = (unsigned char *) malloc(12 * sizeof(unsigned char));
    unsigned char c;
    int i, j;

    image->imageFile = fopen(image->fileName,"r+");

    if (image->imageFile == NULL){
        perror("The following error occurred:");
        return 1;
    }

    for (i=0; i<12; i++)
        string[i] = 0;

    i=0;
    do {
        fscanf(image->imageFile, "%c", &c);
        string[i++] = c;
    } while (c != 0x0a && c != 0x20);
    string[i-1] = 0;

    if (strcmp(string, "P6"))
    {
        printf("Not a PPM file\n");
        return 1;
    }

    free(string);

    c = getc(image->imageFile);
    while (c == '#') {
        while (getc(image->imageFile) != '\n');
        c = getc(image->imageFile);
    }
    ungetc(c, image->imageFile);

    if (fscanf(image->imageFile, "%d %d", &image->width, &image->height) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", image->fileName);
        return 1;
    }

    if (fscanf(image->imageFile, "%d", &i) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", image->fileName);
        return 1;
    }

    if (i!= 255) {
        fprintf(stderr, "'%s' does not have 8-bits components\n", image->fileName);
        return 1;
    }

    while (fgetc(image->imageFile) != '\n') ;

    image->data = (unsigned char*) malloc (3 * image->width * image->height *  sizeof(unsigned char));

    if(fread(image->data, 3 * image->width,  image->height, image->imageFile) != image->height){
        fprintf(stderr, "Error loading image '%s'\n", image->fileName);
        return 1;
    }

    fclose(image->imageFile);
    return 0;
}