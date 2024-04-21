#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>





void readkatalog(char* name, int i)
{	
    DIR *fdir = opendir(name);
    
    
    if (fdir == NULL) {
        printf("Unable to open directory '%s'\n", name);
        return;
    }
    struct dirent *info;
    
    while((info = readdir(fdir)) != NULL){
        if(strcmp(info->d_name,".")==0 || strcmp(info->d_name,"..")==0) continue;
        for(int k=0; k<i; k++) printf("> ");
        printf("%s ", info->d_name);
        struct stat file_info;
        printf(" | ");

        char filename[PATH_MAX];
        snprintf(filename, sizeof(filename), "%s/%s", name, info->d_name);
        
        if (lstat(filename, &file_info) == -1) {
            printf("Cannot get file stat\n");
            continue;
        }
    
        switch (file_info.st_mode & S_IFMT) {
            case S_IFREG:  printf("regular file"); break;
            case S_IFDIR:  printf("directory"); break;
            case S_IFLNK:  printf("symbolic link"); break;
            case S_IFIFO:  printf("FIFO/pipe"); break;
            case S_IFSOCK: printf("socket"); break;
            default:       printf("unknown"); break;
        }
        printf(" | Owner: %s", getpwuid(file_info.st_uid)->pw_name);
        printf(" | Group: %s", getgrgid(file_info.st_gid)->gr_name);
        printf(" | Permissions: %o", file_info.st_mode & 0777);
        printf("\n");
        if (file_info.st_mode & S_IFDIR){
            readkatalog(filename, i+1);
        }
    }
    closedir(fdir);
}

int main()
{
	
	char name[255];
	printf("enter directory name: ");
	scanf("%s",name);
    readkatalog(name,0);
    

    return 0; 
}
