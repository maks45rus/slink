#include "image_redakt.h"

void changeresolution(unsigned char **pixels, int oldWidth, int oldHeight, int newWidth, int newHeight)
{
	int nearestX;
	int nearestY;
	unsigned char *newpixels = (unsigned char*)malloc(newWidth * newHeight * 3 * sizeof(unsigned char));
	for (int y = 0; y < newHeight; y++) {
			for (int x = 0; x < newWidth; x++) {
				nearestX = (x * oldWidth) / newWidth;
				nearestY = (y * oldHeight) / newHeight;
				for (int c = 0; c < 3; c++) {
					newpixels[(y * newWidth + x) * 3 + c] = (*pixels)[(nearestY * oldWidth + nearestX) * 3 + c];
				}
			}
		}
    free(*pixels); 
    *pixels = newpixels;
}



void rotate(unsigned char **pixels, int width, int height)
{
    unsigned char *rotatedPixels = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int c = 0; c < 3; ++c) {
                rotatedPixels[(x * height + y) * 3 + c] = (*pixels)[((height - y - 1)*width + x) * 3 + c];
            }
        }
    }
    free(*pixels);
    *pixels = rotatedPixels;
}


void grayscale(unsigned char **pixels, int width, int height)
{	
	unsigned char *npixels = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
	unsigned char avg;
    for (int i = 0; i < width * height * 3; i += 3) {
        avg = ((*pixels)[i] + (*pixels)[i + 1] + (*pixels)[i + 2]) / 3;

        npixels[i] = avg;
        npixels[i + 1] = avg;
        npixels[i + 2] = avg;
    }
    free(*pixels);
    *pixels=npixels;
}

void negative(unsigned char **pixels, int width, int height)
{	
	unsigned char *npixels = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
	
    for (int i = 0; i < width * height * 3; i += 3) {
      
        npixels[i] = 255-(*pixels)[i];
        npixels[i + 1] = 255-(*pixels)[i+1];
        npixels[i + 2] = 255-(*pixels)[i+2];
    }
    free(*pixels);
    *pixels=npixels;
}

void cutimage(unsigned char **pixels, int width, int height, int startX, int startY, int endX, int endY)
{
	if (startX > endX){
		int tmp;
		tmp = startX;
		startX=endX;
		endX=tmp;
	}
	if (startY > endY){
		int tmp;
		tmp = startY;
		startY=endY;
		endY=tmp;
	}
	if(startY > height) startY = height-1;
	if(startX > width) startX = width-1;
	if (endX > width) endX = width-1;
	if (endY > height) endY = height-1;
	
	int newHeight, newWidth;;
	int oldx, oldy;
	newHeight = abs(endY - startY);
	newWidth = abs(endX - startX);
	if(newHeight == 0) newHeight = 1;
	if(newWidth == 0) newWidth = 1;
	unsigned char *cutPixels = (unsigned char*)malloc(newWidth * newHeight * 3 * sizeof(unsigned char));
    
    for (int y = 0; y < newHeight; y++) {
		oldy=startY+y;
		for (int x = 0; x < newWidth; x++) {
			oldx=startX+x;
			for (int c = 0; c < 3; c++) {
				cutPixels[(y * newWidth + x) * 3 + c] = (*pixels)[(oldy * width + oldx) * 3 + c];
			}
		}
	}
    free(*pixels);
    *pixels = cutPixels;
}

void mirror(unsigned char **pixels, int width, int height, char* vect)
{
    unsigned char *mirroredPixels = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
    int oldpos;
    int newpos;
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			if(strcmp(vect,"h")){
				oldpos = (x + y * width) * 3;
				newpos = (width - x + y * width) * 3;
			}else{
				oldpos = (x + y * width) * 3;
				newpos = (x + (height - y) * width) * 3;		
			}
			for (int c = 0; c < 3; ++c) {
				mirroredPixels[oldpos + c] = (*pixels)[newpos + c];
			}
		}
	}
    free(*pixels);
    *pixels = mirroredPixels;
}

void blur(unsigned char **pixels, int width, int height) {
   
    unsigned char *blurredPixels = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
    if (!blurredPixels) {
        perror("Memory allocation for blurred image failed");
        return;
    }

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int pixelIndex = (y * width + x) * 3 + c;
                
                int sum = 0;
                for (int ny = -1; ny <= 1; ny++) {
                    for (int nx = -1; nx <= 1; nx++) {
                        int currentPixelIndex = ((y + ny) * width + (x + nx)) * 3 + c;
                        sum += (*pixels)[currentPixelIndex];
                    }
                }
                blurredPixels[pixelIndex] = sum / 9;
            }
        }
    }

     free(*pixels);
    *pixels = blurredPixels;
}
