#ifndef IMAGE_REDAKT_H
#define IMAGE_REDAKT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Объявления функций
void changeresolution(unsigned char **pixels, int oldWidth, int oldHeight, int newWidth, int newHeight);
void rotate(unsigned char **pixels, int width, int height);
void grayscale(unsigned char **pixels, int width, int height);
void negative(unsigned char **pixels, int width, int height);
void cutimage(unsigned char **pixels, int width, int height, int startX, int startY, int endX, int endY);
void mirror(unsigned char **pixels, int width, int height, char* vect);
void blur(unsigned char **pixels, int width, int height);

#endif // IMAGE_REDAKT_H
