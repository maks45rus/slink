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

//void copy_dir(const char* src, const char* dest)
//{
    //DIR *dir;
    //struct dirent *entry;
    //struct stat statbuf;
    //char src_path[1024];
    //char dest_path[1024];

    //if (stat(src, &statbuf) == 0) {
        //mkdir(dest, statbuf.st_mode);
    //} else {
        //perror("Failed to get source directory permissions");
        //return;
    //}

    //if (!(dir = opendir(src))) {
        //perror("Failed to open source directory");
        //return;
    //}

    //while ((entry = readdir(dir)) != NULL) {
        //if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            //continue;

        //snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        //snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        //// Recursively copy directories
        //if (entry->d_type == DT_DIR) {
            //copy_dir(src_path, dest_path);
        //} else if (entry->d_type == DT_LNK) {
            //// Create symbolic link
            //ssize_t len;
            //char link_target[1024];
            //if ((len = readlink(src_path, link_target, sizeof(link_target)-1)) != -1) {
                //link_target[len] = '\0';
                //symlink(link_target, dest_path);
            //}
        //} else if (entry->d_type == DT_REG) {
            //// Copy regular file
            //copy_file(src_path, dest_path);
        //} else {
            //// Create empty file for other file types (like FIFO, socket, etc.)
            //int fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, statbuf.st_mode);
            //if (fd >= 0) close(fd);
        //}
    //}
    //closedir(dir);
//}



void copykatalog(char* name,char* newdir)
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
        if(strcmp(info->d_name,".")==0 || strcmp(info->d_name,"..")==0 || strcmp(info->d_name,newdir)==0) continue;
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
				copykatalog(file, newfile);
				break;
            case DT_LNK:
				char link_target[1024];
				int len = readlink(file, link_target, sizeof(link_target)-1);
				link_target[len] = '\0';
				symlink(link_target, newfile);
				break;
			default: 
				int fd = open(newfile, O_WRONLY | O_CREAT | O_TRUNC, file_info.st_mode);
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
    copykatalog(name,"new");
    

    return 0; 
}
