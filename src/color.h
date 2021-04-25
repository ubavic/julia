#ifndef COLOR_H
#define COLOR_H

#include "global.h"

void GetOutside (unsigned int, struct Color*);

void ClassicColor (unsigned int, struct Color*);

void ClassicColor1 (unsigned int, struct Color*);

void ContinuousColor (unsigned int, struct Color*);

void SmoothColor (unsigned int, struct Color*);

void ArgumentColor (unsigned int, struct Color*);

void ContinuousArgumentColor (unsigned int, struct Color*);

void GridColor (unsigned int, struct Color*);

void GridImage (unsigned int, struct Color*);

void GetInside (unsigned int, struct Color*);

void SpeedColor (unsigned int, struct Color*);

void GreenColor (unsigned int, struct Color*);

void DistanceColor (unsigned int, struct Color*);

void BotcherCoordinatesColor (unsigned int, struct Color*);

void BotcherImageColor (unsigned int, struct Color*);

void DiskRainbowColor (unsigned int, struct Color*);

void InsideImage (unsigned int, struct Color*);

void HSVtoRGB (double, double, double, struct Color*);

void AvergePalette (struct Color*, int, struct Color*);

int LoadPalete (char*);

#endif