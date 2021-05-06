#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command, int *argc, char *argv[]);

int main(){
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1]=0;
	int argc = 0;
	char *argv[MAX_ARG] = { NULL };

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin);
		command[strlen(command)-1] = 0;

		if(strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
			break;

		ParseCommand(command, &argc, argv);

		printf("argc = %d\n", argc);
		for(int i=0; i<argc;i++)
			printf("argv[%d] = %s\n", i, argv[i]);
		printf("argv[%d] = %p\n", argc, argv[argc]);
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



