#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp", "touch", "mkdir", "ls", "pwd", "cat", "grep", "chmod", "diff", "cd", "exit", "help"};

int isAllowed(const char *cmd){

	for (int i = 0; i < (sizeof(allowed) / sizeof(allowed[0])); i++){
		if (strcmp(cmd, allowed[i]) == 0){
			return 1;
		}
	}
	return 0;
}

int main(){

	// TODO
	// Add variables as needed

	char line[256];

	while (1){

		fprintf(stderr, "rsh>");

		if (fgets(line, 256, stdin) == NULL)
			continue;

		if (strcmp(line, "\n") == 0)
			continue;

		line[strlen(line) - 1] = '\0';

		// TODO
		// Add code to spawn processes for the first 9 commands
		// And add code to execute cd, exit, help commands
		// Use the example provided in myspawn.c
		char* lineTok;
		char *copyCmd = strdup(line);
		lineTok = strtok (copyCmd," ");

		if (isAllowed(lineTok)){
			if (strcmp(lineTok, "cd") == 0){
				char copyLine[256];
				int counter = 1;
				strcpy(copyLine, line);
				char *lineTok;
				lineTok = strtok(copyLine," ");

				while (lineTok != NULL){
					counter++;
					lineTok = strtok(NULL, " ");
				}
				
				if(counter > 3){
					printf("-rsh: cd: too many arguments\n");
				}

				char* directory = &(line[strlen(line)-1]);
				chdir(directory);
			}

			if (strcmp(lineTok, "exit") == 0){
				break;
			}

			if (strcmp(lineTok, "help") == 0){
				printf("1: cp\n");
				printf("2: touch\n");
				printf("3: mkdir\n");
				printf("4: ls\n");
				printf("5: pwd\n");
				printf("6: cat\n");
				printf("7: grep\n");
				printf("8: chmod\n");
				printf("9: diff\n");
				printf("10: cd\n");
				printf("11: exit\n");
				printf("12: help\n");
			}
		}

		else{
			printf("NOT ALLOWED!\n");
		}
		free(copyCmd);
	}

	
	return 0;
}
