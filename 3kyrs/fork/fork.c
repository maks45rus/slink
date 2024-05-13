#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

typedef struct {
    char s_name[50];
    int s_count;
} statserver;

void readfile(char* filename, char* resultfile, char* argv0)
{  	
	
	int servercount=0;
	int exist;
	FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s.\n", filename);
        return;
    }
    statserver *server = malloc(50 * sizeof(statserver));
	
    char line[4000];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)!=NULL){
		exist = 0;
		char* token = strtok(line, ";");
		for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
        }
        
        for (int i = 0; i < servercount; i++) {
            if (strcmp(server[i].s_name, token) == 0) {
                server[i].s_count += 1;
                exist = 1;
                continue;
            }
        }
        if (!exist) {
			//
            strcpy(server[servercount].s_name, token);
            server[servercount].s_count = 1;
            servercount++;
        }
    }
    fclose(file);
	FILE* ban = fopen(argv0,"r");
	flock(fileno(ban), LOCK_EX);
	FILE* result = fopen(resultfile, "r");
	
	statserver checkresult;
	while(fscanf(result, "%[^:]: %d\n",checkresult.s_name,&checkresult.s_count)==2){
		sleep(1);
		exist = 0;
		int i = 0;
		for(i=0; i<servercount; i++){
			if(strcmp(checkresult.s_name,server[i].s_name)==0){
				exist = 1;
				break;
			}
			
		}
		if(!exist){
			//
			strcpy(server[servercount].s_name,checkresult.s_name);
			server[servercount].s_count = checkresult.s_count;
			servercount++;	
		}else{
			server[i].s_count += checkresult.s_count;
		}
	}
	result = freopen(resultfile,"w",result);
	for (int i = 0; i < servercount; i++) {
		sleep(1);
		fprintf(result, "%s: %d\n", server[i].s_name, server[i].s_count);
	}
	fclose(result);
	flock(fileno(ban), LOCK_EX);
	fclose(ban);
    free(server);
}

int main(int argc, char** argv)
{
    int i;
    if (argc < 3) {
        printf("Необходимо указать имя файла результата и хотя бы один файл журнала.\n");
        return 1;
    }
    FILE* result = fopen(argv[1], "w");
	if (!result) {
		printf("Не удалось открыть файл %s.\n", argv[1]);
		return 1;
	}
	fclose(result);
    for (i = 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Ошибка создания процесса.\n");
            return 1;
        } else if (pid == 0) {
            readfile(argv[i], argv[1], argv[0]);
            return 0;
        }
    }

    for (i = 2; i < argc; i++)
        wait(NULL);

    return 0;
}
