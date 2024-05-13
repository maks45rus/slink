#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct{
    char format[3];
    int    width;
    int    height;
    int    maxColorValue;
} PPMHeader;

//================================================================
//================================================================
//================================================================

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
	
	//printf("startX - %d startY - %d endX - %d endY - %d\n",startX,startY,endX,endY);
	
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



//================================================================
//================================================================
//================================================================

int fileExists(const char *filename) {
    
	return access(filename, F_OK) != -1;;
    
}

int readimage(char *filename, PPMHeader *head, unsigned char **pixels)
{
	FILE* image = fopen(filename, "r+b");
    if (image == NULL) {
        return -1;
    }
    fscanf(image, " %s",  head->format);
    if(strcmp(head->format,"P6")!=0){
		fclose(image);
		printf("error format.\n use format PPM P6\n");
		return -1;
	}
	
    char c;
    fseek(image,1,SEEK_CUR);
    if((c = fgetc(image))=='#'){
		while ((c = fgetc(image)) != EOF && c != '\n')
			printf("%c", c);
	}else fseek(image,-1,SEEK_CUR);
	
	fscanf(image, "%d %d", &head->width, &head->height);
    fscanf(image, "%d", &head->maxColorValue);
	*pixels = (unsigned char *)malloc(head->width * head->height * 3 * sizeof(unsigned char));
    if (*pixels == NULL) {
        perror("Memory allocation failed");
        fclose(image);
        return -1;
    }
	fseek(image,+1,SEEK_CUR);
    fread(*pixels, sizeof(unsigned char), head->width * head->height * 3, image);
    fclose(image);
	return 0;
}


int newimage(char *filename, PPMHeader head, unsigned char *pixels)
{	
	FILE* image=fopen(filename,"wb");
	if (image == NULL){
		perror("error creating\n");
        return -1;
    }
    fseek(image, 0, SEEK_SET);
	fprintf(image, "%s\n%d %d\n%d\n", head.format, head.width, head.height, head.maxColorValue);
    fwrite(pixels, sizeof(unsigned char), head.width * head.height * 3, image);
    fclose(image);
    return 0;
}

int main(int argc, char **argv)
{	
	int startX, endX, startY, endY;
	int newwidth, newheight;
	unsigned char *pixels;
	char newfilename[20];
	char filename[20];
	PPMHeader head;
	int choice=0;
	char ch;
	
	printf("Enter image name(ONLY .ppm): ");
	scanf("%s", filename);
	
	if(readimage(filename, &head,&pixels)!=0){
		perror("error reading image\n");
		return -1;
	}
	
	printf("create new image?(y/n): ");
	scanf(" %c", &ch);
	if(ch == 'y' || ch == 'Y'){
		int created=0;
		while(created==0){
			printf("Enter new image name: ");
			scanf("%s", newfilename);
			if(fileExists(newfilename)){
				printf("file with name \"%s\" exists.\n", newfilename);
			}else{
				created=1;
				newimage(newfilename, head, pixels);
				strcpy(filename, newfilename);
			}
		}
	}
	
rdimg:
	if(readimage(filename, &head,&pixels)!=0){
		perror("error reading image\n");
		return -1;
	}
	
	printf("format: %s\n", head.format);
	printf("width px: %d\n", head.width);
	printf("height px: %d\n", head.height);
	printf("color: %d\n", head.maxColorValue);
	
	
	printf("Choose what to do\n");
	printf("\n1-change resolution\n2-rotate\n3-gray\n4-cut\n0-exit\n");
	scanf("%d",&choice);
	switch(choice) {
		case 0:
			free(pixels);
			break;
		case 1:
			printf("new resolution: ");
			scanf("%d %d",&newwidth,&newheight);
			if(!newwidth || !newheight){
				free(pixels);
				break;
			}
			changeresolution(&pixels, head.width, head.height, newwidth, newheight);
			head.width=newwidth;
			head.height=newheight;
			newimage(filename, head, pixels);
			free(pixels);
			goto rdimg;
		case 2:
			rotate(&pixels,head.width,head.height);
			newwidth=head.height;
			newheight=head.width;
			head.width=newwidth;
			head.height=newheight;
			newimage(filename,head,pixels);
			printf("image rotated\n\n");
			free(pixels);
			goto rdimg;
		case 3:
			grayscale(&pixels,head.width,head.height);
			newimage(filename,head,pixels);
			printf("image grayed\n\n");
			goto rdimg;
		case 4:
			printf("enter coordinats top-left point: \n");
			scanf("%d %d", &startX, &startY);
			printf("enter coordinats bot-right point: \n");
			scanf("%d %d", &endX, &endY);
			cutimage(&pixels, head.width, head.height, startX, startY, endX, endY);
			head.height = abs(endY - startY);
			head.width = abs(endX - startX);
			if(head.height == 0) head.height = 1;
			if(head.width == 0) head.width = 1;
			newimage(filename,head,pixels);
			printf("image cutted\n\n");
			free(pixels);
			goto rdimg;
		default:
			printf("unknown choice. try again\n\n");
			goto rdimg;
	}
	return 0;
}

