#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s username\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    FILE *passwd = fopen("/etc/passwd", "r");
    if (passwd == NULL) {
        perror("error reading /etc/passwd");
        return 1;
    }

    char line[1024];
    int userfound = 0;
    while (fgets(line, sizeof(line), passwd)) {
        char* token = strtok(line, ":");
        if (strcmp(token, username) == 0) {
            userfound = 1;
            break;
        }
    }
    fclose(passwd);
    
    if (!userfound) {
        printf("user not found\n");
        return 1;
    }

    char groupmates[1024] = "";
    FILE *group = fopen("/etc/group", "r");
    if (group == NULL) {
        perror("error reading /etc/group");
        return 1;
    }

    while (fgets(line, sizeof(line), group)) {
        strtok(line, ":");
        strtok(NULL, ":");
        strtok(NULL, ":");
        char* users = strtok(NULL, "\n");

        if (users != NULL && strstr(users, username)) {
          
            char* user_token = strtok(users, ",");
            while (user_token != NULL) {
                if ((strcmp(user_token, username) != 0) && (strstr(groupmates,user_token) == 0)) { 
                 
                    strcat(groupmates, user_token);
                    strcat(groupmates, ",");
                }
                user_token = strtok(NULL, ",");
            }
        }
    }
    fclose(group);

    int len = strlen(groupmates);
    if (len > 0) {
        groupmates[len - 1] = '\0';
    }

    printf("%s\n", groupmates);
    return 0;
}

