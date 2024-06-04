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



void copykatalog(char* name,char* newdir,char* newdirname)
{
	struct stat dir_info;
	if (lstat(name, &dir_info) == -1) {
		printf("Cannot get file stat\n");
    }
    mkdir(newdir, dir_info.st_mode);
	
	DIR *fdir = opendir(name);
    if (fdir == NULL) {
        printf("Unable to open directory '%s'\n", name);
        return;
    }
	struct dirent *info;
	while((info = readdir(fdir)) != NULL){
        if(strcmp(info->d_name,".")==0 || strcmp(info->d_name,"..")==0 || strcmp(info->d_name,newdirname)==0) continue;
        char file[PATH_MAX];
        char newfile[PATH_MAX];
        
        snprintf(file, sizeof(file), "%s/%s", name, info->d_name);
        snprintf(newfile, sizeof(newfile), "%s/%s", newdir, info->d_name);
        
        struct stat file_info;
		if (lstat(file, &file_info) == -1) {
			printf("Cannot get file stat\n");
		}
		
        switch (info->d_type) {
            case DT_DIR:
				copykatalog(file, newfile, newdirname);
				break;
            case DT_LNK:
				char link_target[1024];
				int len = readlink(file, link_target, sizeof(link_target)-1);
				link_target[len] = '\0';
				symlink(link_target, newfile);
				break;
			default: 
				int fd = open(newfile, O_CREAT, file_info.st_mode);
				chmod(newfile, file_info.st_mode & 07777);
				if (fd >= 0) close(fd);
				break;
        }
        
    }
    
    closedir(fdir);
    
}


int main()
{
	
	char name[255];
	printf("enter directory name: ");
	scanf("%s",name);
    copykatalog(name,"new", "new");
    

    return 0; 
}
