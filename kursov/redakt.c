#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "image_redakt.h"
typedef struct{
    char format[3];
    int    width;
    int    height;
    int    maxColorValue;
} PPMHeader;

void printhelp()
{
	printf("usage:  ./redakt inputimage.ppm [option] result.ppm\n");

printf("options:\n");
printf("-showstat \t\tDisplay image statistics (format, width, height, color depth)\n");
printf("-blur \t\t\tApply a blur effect to the image\n");
printf("-rotate \t\tRotate the image 90 degrees clockwise\n");
printf("-gray \t\t\tConvert the image to grayscale\n");
printf("-negative \t\tInvert the colors of the image to their negatives\n");
printf("-size geometry \t\tChange the resolution of the image to the specified width and height\n");
printf("-cut point1 point2 \tCut the image from point1 to point2, specifying top left and bottom right corners\n");
printf("-mirror direction(v/h) \tMirror the image vertically (v) or horizontally (h)\n");
}


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
		while ((c = fgetc(image)) != EOF && c != '\n');
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

int interactivemode();

int main(int argc, char **argv)
{	
	if(argc == 1){
	int er = interactivemode();
	return er;
	}
	if(strcmp(argv[1],"-help")==0){
	printhelp();
	return 0;
	}
	if(argc<3){
	printhelp();
	return 1;
	}
	
	unsigned char *pixels;
	PPMHeader head;
	char* filename;
	
	filename = argv[1];
	
	if(readimage(filename, &head,&pixels)!=0){
		perror("error reading image\n");
		return -1;
	}
	
	int startX, endX, startY, endY;
	int newwidth, newheight;
	char* newfilename;
	char* choice;
	int a = 0;
	
	newfilename = argv[3];
	choice = argv[2];
	
	if(strcmp(choice,"-showstat")==0){
		a = 1;
		printf("format: %s\n", head.format);
		printf("width px: %d\n", head.width);
		printf("height px: %d\n", head.height);
		printf("color: %d\n", head.maxColorValue);
		free(pixels);
		return 0;
	}
	if(argc<4){
			printhelp();
			free(pixels);
			return 1;
		}
		
	if(strcmp(choice,"-rotate")==0){
		a = 1;
		rotate(&pixels,head.width,head.height);
		newwidth=head.height;
		newheight=head.width;
		head.width=newwidth;
		head.height=newheight;
		newimage(newfilename,head,pixels);
		printf("image rotated\n");
	}
	if(strcmp(choice,"-gray")==0){
		a = 1;
		grayscale(&pixels,head.width,head.height);
		newimage(newfilename,head,pixels);
		printf("image grayed\n");
	}
	if(strcmp(choice,"-blur")==0){
		a = 1;
		blur(&pixels,head.width,head.height);
		newimage(newfilename,head,pixels);
		printf("image blured\n");
	}
	if(strcmp(choice,"-negative")==0){
		a = 1;
		negative(&pixels,head.width,head.height);
		newimage(newfilename,head,pixels);
		printf("image negatived\n");
	}
	if(strcmp(choice,"-mirror")==0){
		a = 1;
		if(argc<5){
			printhelp();
			free(pixels);
			return 1;
		}
		//if(argv[4] == NULL) 
			//newfilename = filename;
		//else
		newfilename = argv[4];
		if(strcmp(argv[3],"v")==0){
			mirror(&pixels,head.width,head.height,"v");
		}else if(strcmp(argv[3],"h")==0){
			mirror(&pixels,head.width,head.height,"h");
		}else{
			printhelp();
			free(pixels);
			return 1;
		}
		newimage(newfilename,head,pixels);
		printf("image mirrored\n");
	}
	if(strcmp(choice,"-cut")==0){
		a = 1;
		if(argc<8){
			printhelp();
			free(pixels);
			return 1;
		}
		//if(argv[7] == NULL) 
			//newfilename = filename;
		//else
		newfilename = argv[7];
		endY = atoi(argv[6]);
		endX = atoi(argv[5]);
		startY = atoi(argv[4]);
		startX = atoi(argv[3]);
		
		cutimage(&pixels, head.width, head.height, startX, startY, endX, endY);
		head.height = abs(endY - startY);
		head.width = abs(endX - startX);
		if(head.height == 0) head.height = 1;
		if(head.width == 0) head.width = 1;
		newimage(newfilename,head,pixels);
		printf("image cutted\n");
	}
	if(strcmp(choice,"-size")==0){
		a = 1;
		if(argc<5){
			printhelp();
			free(pixels);
			return 1;
		}
		//if(argv[5] == NULL) 
			//newfilename = filename;
		//else
		newfilename = argv[5];
		newheight = atoi(argv[4]);
		newwidth = atoi(argv[3]);
		changeresolution(&pixels, head.width, head.height, newwidth, newheight);
		head.width=newwidth;
		head.height=newheight;
		newimage(newfilename, head, pixels);
		printf("size changed\n");
	}
	if(a == 0){
		printhelp();
	}

	free(pixels);
	return 0;
}

int interactivemode()
{
	int startX, endX, startY, endY;
	int newwidth, newheight;
	unsigned char *pixels;
	char newfilename[20];
	char filename[20];
	char direction;
	PPMHeader head;
	int choice=0;
	char ch;
	
	printf("Enter image name(ONLY .ppm): ");
	scanf("%s", filename);
	
	if(readimage(filename, &head,&pixels)!=0){
		perror("error reading image\n");
		return -1;
	}
	
	printf("create new image?(y/n(edit current file)): ");
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
	printf("-----------------------\n");
	printf("\nChoose what to do\n");
	printf("\n1-showstat\n2-rotate\n3-gray\n4-cut\n5-mirror\n");
	printf("6-negative\n7-blur\n8-change resolution\n0-exit\n");
	scanf("%d",&choice);
	switch(choice) {
		case 0:
			free(pixels);
			break;
		case 1:
			printf("format: %s\n", head.format);
			printf("width px: %d\n", head.width);
			printf("height px: %d\n", head.height);
			printf("color: %d\n", head.maxColorValue);
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
			free(pixels);
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
		case 5:
			printf("enter directin(v/h): \n");
			scanf(" %c", &direction);
			printf("\n");
			if(direction == 'v'){
				mirror(&pixels,head.width,head.height,"v");
			}else if(direction == 'h'){
				mirror(&pixels,head.width,head.height,"h");
			}else{
				printf("error directin\n");
				free(pixels);
				goto rdimg;
			}
			newimage(filename,head,pixels);
			printf("image mirrored\n\n");
			free(pixels);
			goto rdimg;
		case 6:
			negative(&pixels,head.width,head.height);
			newimage(filename,head,pixels);
			printf("image negatived\n");
			free(pixels);
			goto rdimg;
		case 7:
			blur(&pixels,head.width,head.height);
			newimage(filename,head,pixels);
			printf("image blured\n");
			free(pixels);
			goto rdimg;
		case 8:
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
			printf("resolution changed\n\n");
			goto rdimg;
		default:
			printf("unknown choice. try again\n\n");
			free(pixels);
			goto rdimg;
	}
	return 0;

}

