#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    char s_name[50];
    int s_count;
} statserver;

void readfile(char* filename, char* resultfile, int a)
{  	
	printf("start %d\n",a);
	int servercount=0;
	int exist;
	FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s.\n", filename);
        return;
    }
    statserver *server = malloc(20 * sizeof(statserver));
	
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
            strcpy(server[servercount].s_name, token);
            server[servercount].s_count = 1;
            servercount++;
        }
    }
    fclose(file);
    printf("stop %d\n",a);
    FILE* result = fopen(resultfile, "a+");
	if (!result) {
		printf("Не удалось открыть файл %s.\n", resultfile);
		fclose(file);
		free(server);
		return;
	}
	
	flock(fileno(result), LOCK_EX);
	for (int i = 0; i < servercount; i++) {
		fprintf(result, "%s: %d\n", server[i].s_name, server[i].s_count);
	}
	flock(fileno(result), LOCK_UN);
	fclose(result);
    free(server);
}

int main(int argc, char** argv)
{
    int i;
    if (argc < 3) {
        printf("Необходимо указать имя файла результата и хотя бы один файл журнала.\n");
        return 1;
    }
    for (i = 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Ошибка создания процесса.\n");
            return 1;
        } else if (pid == 0) {
            readfile(argv[i], argv[1], i);
            return 0;
        }
    }

    for (i = 2; i < argc; i++)
        wait(NULL);

    return 0;
}
