#include "color.h"
#include "image.h"

extern struct Image inputImage;
extern struct Palette mainPalette;
extern struct Fractal fractal;

void GetInside (unsigned int i, struct Color *color)
{
    *color = mainPalette.insideColor;
}

void GetOutside (unsigned int i, struct Color *color)
{
    *color = mainPalette.palette[0];
}

void ClassicColor (unsigned int i, struct Color *color)
{
    *color = mainPalette.palette[i % mainPalette.colors];
}

void ClassicColor1 (unsigned int i, struct Color *color)
{
    double d = ((double) i)/fractal.iterations;
    color->r = mainPalette.palette[0].r * (1 - d) + mainPalette.palette[1].r * d;
    color->g = mainPalette.palette[0].g * (1 - d) + mainPalette.palette[1].g * d;
    color->b = mainPalette.palette[0].b * (1 - d) + mainPalette.palette[1].b * d;
}

void ContinuousColor (unsigned int i, struct Color *color)
{
    double mu = i - (fractal.rho - fractal.radius)/(pow(fractal.radius, fractal.exponent) - fractal.radius);

    int clr1 = (int) mu;
    double t2 = mu - clr1;
    double t1 = 1 - t2;
    clr1 = clr1 % mainPalette.colors;
    int clr2 = (clr1 + 1) % mainPalette.colors;

    color->r = mainPalette.palette[clr1].r * t1 + mainPalette.palette[clr2].r * t2;
    color->g = mainPalette.palette[clr1].g * t1 + mainPalette.palette[clr2].g * t2;
    color->b = mainPalette.palette[clr1].b * t1 + mainPalette.palette[clr2].b * t2;
}

void SmoothColor (unsigned int i, struct Color *color)
{
    double mu = i + 2 - log(log(sqrt(fractal.rho)))/log(fractal.exponent);
    
    int clr1 = (int) mu;
    double t2 = mu - clr1;
    double t1 = 1 - t2;
    clr1 = clr1 % mainPalette.colors;
    int clr2 = (clr1 + 1) % mainPalette.colors;

    color->r = mainPalette.palette[clr1].r * t1 + mainPalette.palette[clr2].r * t2;
    color->g = mainPalette.palette[clr1].g * t1 + mainPalette.palette[clr2].g * t2;
    color->b = mainPalette.palette[clr1].b * t1 + mainPalette.palette[clr2].b * t2;
}

void ArgumentColor (unsigned int i, struct Color *color)
{
    if (fractal.orbit[fractal.kappa].re > 0 && fractal.orbit[fractal.kappa].im > 0) 
        *color = mainPalette.palette[0];
    else if (fractal.orbit[fractal.kappa].re < 0 && fractal.orbit[fractal.kappa].im > 0)
        *color = mainPalette.palette[1];
    else if (fractal.orbit[fractal.kappa].re < 0 && fractal.orbit[fractal.kappa].im < 0)
        *color = mainPalette.palette[2];
    else
        *color = mainPalette.palette[3];
}

void ContinuousArgumentColor (unsigned int i, struct Color *color)
{
    double angle = atan2(fractal.orbit[fractal.kappa].im, fractal.orbit[fractal.kappa].re) * IPI + 0.5;
    unsigned int n = ((int)(mainPalette.colors * angle)) % mainPalette.colors;
    unsigned int m = (n + 1) % mainPalette.colors;
    angle = angle*mainPalette.colors - n;
    color->r = mainPalette.palette[n].r * (1 - angle) + mainPalette.palette[m].r * angle;
    color->g = mainPalette.palette[n].g * (1 - angle) + mainPalette.palette[m].g * angle;
    color->b = mainPalette.palette[n].b * (1 - angle) + mainPalette.palette[m].b * angle;
}

void GridColor (unsigned int i, struct Color *color)
{
    i--;
    double angle = atan2(fractal.orbit[i].im, fractal.orbit[i].re) * IPI + 0.5;
    double mu = i + 1 - log(log(sqrt(fractal.rho))) / log(fractal.exponent);
    double ro = (fractal.rho - fractal.radius) / (pow(fractal.radius, fractal.exponent) - fractal.radius);
    int m = ro < 0.80 ? 1 : 0;
    int a = angle > (0.495 - ro * 0.005) && angle < (0.505 + ro * 0.005) ? 0 : 1;
    if (a && m)
        *color = mainPalette.palette[1];
    else
        *color = mainPalette.palette[0];
}

void GridImage (unsigned int i, struct Color *color)
{
    i--;
    double angle = atan2(fractal.orbit[i].im, fractal.orbit[i].re) / (PI * 2) + 0.5;
    //double ro = 2 - log(0.5*(log(fractal.rho) - fractal.exponent));
    double ro = log(log(sqrt(fractal.rho)) / log(sqrt(fractal.radius))) / log(fractal.exponent);
    int m = ro < 1 && ro > 0 ? 1 : 0;
    if (m) {
        int j = ro * inputImage.height;
        int k = angle * inputImage.width;
        i = 3 * (int)(j * (inputImage.width) + k);
        color->r = inputImage.row[i];
        color->g = inputImage.row[i+1];
        color->b = inputImage.row[i+2];
    }
}

void InsideImage (unsigned int i, struct Color *color)
{
    int j = (fractal.orbit[fractal.kappa].im / 4 + 0.5) * inputImage.height;
    int k = (fractal.orbit[fractal.kappa].re / 4 + 0.5) * inputImage.width;
    if (j > 0 && k > 0 && j < inputImage.height && k < inputImage.width) {
        i = 3 * (int) (j * inputImage.width + k);
        color->r = inputImage.row[i];
        color->g = inputImage.row[i+1];
        color->b = inputImage.row[i+2];
    } else {
        *color = mainPalette.insideColor;
    }
}

void DiskRainbowColor (unsigned int i, struct Color *color)
{
    HSVtoRGB (
        atan2(fractal.orbit[fractal.kappa].im, fractal.orbit[fractal.kappa].re) / (2 * PI),
        pow(
            NormSq(fractal.orbit[fractal.kappa]) / fractal.radius, 0.05),
            1 - sin(PI * NormSq(fractal.orbit[fractal.kappa]) / (fractal.radius * 2) *
                sin(PI * NormSq(fractal.orbit[fractal.kappa]) / (fractal.radius * 2))),
        color);
}

void SpeedColor (unsigned int i, struct Color *color)
{
    double mu =  NormSq(
        Sub(fractal.orbit[i],fractal.orbit[i-fractal.kappa])) /
        NormSq(Sub(fractal.orbit[i-fractal.kappa],fractal.orbit[i-2*fractal.kappa])
        );
    mu = log(mu + 1);
    int clr1 = (int) mu;
    double t2 = mu - clr1;
    double t1 = 1 - t2;
    clr1 = clr1 % mainPalette.colors;
    int clr2 = (clr1 + 1) % mainPalette.colors;

    color->r = mainPalette.palette[clr1].r * t1 + mainPalette.palette[clr2].r * t2;
    color->g = mainPalette.palette[clr1].g * t1 + mainPalette.palette[clr2].g * t2;
    color->b = mainPalette.palette[clr1].b * t1 + mainPalette.palette[clr2].b * t2;
}

void GreenColor (unsigned int i, struct Color *color)
{
    double mu = i - log(log(fractal.rho)/2)/log(fractal.exponent);
    double t1 = 2*atan(mu)/PI;
    t1 = t1*t1;
    double t2 = 1 - t1;

    color->r = mainPalette.palette[0].r * t2 + mainPalette.palette[1].r * t1;
    color->g = mainPalette.palette[0].g * t2 + mainPalette.palette[1].g * t1;
    color->b = mainPalette.palette[0].b * t2 + mainPalette.palette[1].b * t1;
}

void DistanceColor (unsigned int i, struct Color *color)
{
    complex dz = O;

    for (int j = 0; j < i; j++)
        dz = Add(Mul((complex){.re=fractal.exponent, .im=0}, Mul(dz, fractal.orbit[j])), (complex){.re=1, .im=0});

    double t1 = sqrt(NormSq(fractal.orbit[i])/ NormSq(dz)) * log(sqrt(NormSq(fractal.orbit[i]))) ;
    t1 = 2 * atan(t1) / PI;
    double t2 = 1 - t1;

    color->r = mainPalette.palette[0].r * t2 + mainPalette.palette[1].r * t1;
    color->g = mainPalette.palette[0].g * t2 + mainPalette.palette[1].g * t1;
    color->b = mainPalette.palette[0].b * t2 + mainPalette.palette[1].b * t1;
}

void BotcherCoordinatesColor (unsigned int i, struct Color *color)
{
    int a = 0;

    complex phi = fractal.orbit[0];
    complex mul;

    for (int j = 0; j < i; j++) {
        mul = Mul(fractal.orbit[j],fractal.orbit[j]);
        mul = Add((complex){.re=1, .im=0}, Div(fractal.constant, mul));
        mul = RealExp(mul, pow(0.5, j+1));
        phi = Mul(phi, mul);
    }

    int angle = floor((64 * (atan2(phi.im, phi.re) + PI)) / (2 * PI));
    int ro = 8 * log(Norm(phi));

    *color = mainPalette.palette[(angle + ro) % mainPalette.colors];
}

void BotcherImageColor (unsigned int i, struct Color *color)
{
    int a = 0;

    complex phi = fractal.orbit[0];
    complex mul;

    for (int j = 0; j < i; j++) {
        mul = Mul(fractal.orbit[j], fractal.orbit[j]);
        mul = Add((complex){.re=1, .im=0}, Div(fractal.constant, mul));
        mul = RealExp(mul, pow(0.5, j + 1));
        phi = Mul(phi, mul);
    }

    double angle = (32 * (atan2(phi.im, phi.re) + PI)) / (2 * PI);
    angle = angle - floor(angle);
    double ro = 6 * log(Norm(phi));
    ro = ro - floor(ro);

    int j = ro * inputImage.height;
    int k = angle * inputImage.width;
    i = 3 * (int) (j * inputImage.width + k);
    color->r = inputImage.row[i];
    color->g = inputImage.row[i+1];
    color->b = inputImage.row[i+2];
}

void HSVtoRGB (double H, double S, double V, struct Color *color)
{
    double i, f, p, q, t, r, g, b;
    
    if (S == 0)
        r = g = b = V;
    else {
        H = 6 * (H - floorf(H));
        int ii = i = floorf(H);
        f = H - i;
        p = V * (1 - S);
        q = V * (1 - (S * f));
        t = V * (1 - (S * (1 - f)));
        switch(ii) {
            case 0: r = V; g = t; b = p; break;
            case 1: r = q; g = V; b = p; break;
            case 2: r = p; g = V; b = t; break;
            case 3: r = p; g = q; b = V; break;
            case 4: r = t; g = p; b = V; break;
            default:r = V; g = p; b = q; break;
        }
    }

    color->r = 0xFF * r;
    color->g = 0xFF * g;
    color->b = 0xFF * b;
}

void AvergePalette (struct Color *palette, int n, struct Color *color) 
{
    int r = 0, g = 0, b = 0;
    int i;

    for (i = 0; i < n; i++) {
        r += palette[i].r;
        g += palette[i].g;
        b += palette[i].b;
    }

    color->r = r / n;
    color->g = g / n;
    color->b = b / n;
}


int LoadPalete (char *fileName)
{
    int n, i = 0, first = 0;
    FILE *inputFile;
    char string[16];

    inputFile = fopen(fileName,"r");

    if (inputFile == NULL) {
        perror("The following error occurred:");
        return 1;
    }

    while (fscanf(inputFile, "%s", string) == 1) {

        if (strlen(string) != 7)
            continue;

        i++;
    }

    if (i < 3) {
        printf("You must give 3 or more colors. Using default palette.\n");
        mainPalette.palette = defaultPalette;
        mainPalette.colors = 3;
        fclose(inputFile);
        return 0;
    }

    mainPalette.palette = (struct Color *) malloc(i * sizeof(struct Color));

    if (mainPalette.palette == NULL) {
        perror("The following error occurred:");
        fclose(inputFile);
        return 1;
    }

    fseek(inputFile, 0, SEEK_SET);
    mainPalette.colors = 0;

    while (fscanf(inputFile, "%s", string) == 1) {

        if (strlen(string) != 7)
            continue;

        n = (int) strtol(&string[1], NULL, 16);

        if (!first) {
            mainPalette.insideColor.r = n >> 16;
            mainPalette.insideColor.g = n >> 8 & 0xFF;
            mainPalette.insideColor.b = n & 0xFF;
            first = 1;
            continue;
        }

        mainPalette.palette[mainPalette.colors].r = n >> 16;
        mainPalette.palette[mainPalette.colors].g = n >> 8 & 0xFF;
        mainPalette.palette[mainPalette.colors].b = n & 0xFF;
        mainPalette.colors++;
    }
    
    AvergePalette(mainPalette.palette, mainPalette.colors, &mainPalette.avergeColor);

    fclose(inputFile);
    return 0;
}
