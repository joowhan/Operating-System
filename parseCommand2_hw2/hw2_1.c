#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command, int *argc, char *argv[]);

int main(){

	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1]=0;
	int argc = 0;
	char curr[100];
	char *argv[MAX_ARG] = { NULL };
	
	while(1){
		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin);
		command[strlen(command)-1] = 0;

		if(strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
			break;
		
		ParseCommand(command, &argc, argv);
		//parseCommand store the command
		if(strcmp(command, "ls") == 0)
			system("ls");
		else if(strcmp(command, "mkdir") == 0)
			mkdir(argv[1], 0755);
		else if(strcmp(command, "rmdir") == 0)
			rmdir(argv[1]);
		else if(strcmp(command, "cd") == 0){
			if(strcmp(argv[1], "..") ==0 || strcmp(argv[1], "../") == 0)
				chdir("..");
			else chdir(argv[1]);
		}	
		else if(strcmp(command, "curdir") == 0){
			printf("%s\n",getcwd(curr, 100));
		}	
		/*for(int i=0; i<argc;i++) //if mkdir new_dir -> argc = 2, argv[0] = mkdir, argv[1] = new_dir
			printf("argv[%d] = %s\n", i, argv[i]);
		printf("argv[%d] = %p\n", argc, argv[argc]);*/
	}

	printf("Bye!\n");
	return 0 ;


}

void ParseCommand(char *command, int *argc, char *argv[]){
	*argc = 0;
	/*//char *ptr = NULL;
	char *temp[10] = {NULL};
	int i=0;
	char *ptr = strtok(command, " ");
	while(ptr != NULL){
		temp[i] = ptr;
		argv[*argc] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}*/
		
	
	char *temp = NULL;
	char *ptr = NULL;
	int i =0;
	ptr = strtok_r(command, " ", &temp);
	argv[*argc] = ptr;
	while(ptr != NULL){
		if(temp[0] == '\''){
			ptr = strtok_r(NULL, "\"", &temp);
			(*argc)++;
			argv[*argc] = ptr;
		}
		else if(temp[0] =='\"'){
			ptr = strtok_r(NULL, "\"", &temp);
			(*argc)++;
			argv[*argc] = ptr;
		}
		else{
			ptr = strtok_r(NULL, " ", &temp);
			(*argc)++;
			argv[*argc] = ptr;
		}
		if(temp == 0){
			(*argc)++;
			argv[*argc] = temp;
			break;
		}
	}
	argv[*argc] = NULL;
}

