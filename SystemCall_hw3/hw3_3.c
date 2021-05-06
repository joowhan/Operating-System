#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 512
#define MAX_CMD 2048
#define MAX_ARG 256

char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len);
void ParseCommand(char *command, int *argc, char *argv[]);

int main(int argc, char *argv[]){
	int check = 0;
	int file = open("cmd.sh", O_RDONLY);
	char command[MAX_CMD];
	int arc = 0;
	char *arv[MAX_ARG] = { NULL };
	while(check != EOF) {
		check = ReadTextLine(file, command, 2048);
		if(check == EOF) break;
		printf("command = [%s]\n", command);
		command[strlen(command)] = 0;

		ParseCommand(command, &arc, arv);
		//test
		/*
		printf("argc = %d\n", arc);
		for(int i=0; i<arc;i++)
			printf("argv[%d] = %s\n", i, arv[i]);
		*/
		arv[arc]=NULL;
		if(strcmp(arv[0], "cd") ==0){
			chdir(arv[1]);
		}
		if(strcmp(arv[0], "#") == 0) continue;

		else{
			pid_t child_pid = fork();
			if(child_pid < 0){
				fprintf(stderr,"fork failed\n");
				exit(-1);
			}
			else if(child_pid == 0){ //child process
				execvp(arv[0], arv);
				if(check == EOF) break;
				close(file);
				exit(0);
			}
			else{
				wait(NULL);
				if(check == EOF){
					close(file);
					break;
				}
				//exit(0);
			}
		}
		/*if(check == EOF) {
			close(file);
			break;
		}*/

	}
	close(file);
	exit(0);
}

int ReadTextLine(int fd, char str[], int max_len) {
	int i = 0;
	int j =0;
	int ret = 0;

	if(lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;

	while(j < max_len -1) {
		if(buffer_pos == buffer_size) {
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
		}

		if(buffer_size == 0) {
			if(j==0) ret = EOF;
			break;
		}

		while(j < max_len - 2 && buffer_pos < buffer_size){
			str[j++] = buffer[buffer_pos++];
			if(str[j - 1] == '\0' || str[j - 1] == 10){
				j--; //to remove CR
				max_len = j; // toterminate outer loop
				break; //break inner loop
			}

		}
	}
	str[j] = 0;
	return ret;
}


void ParseCommand(char *command, int *argc, char *argv[]){
	*argc = 0;
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
