#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 512

char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len);

int main() {
	int cpu = open("/proc/cpuinfo", O_RDONLY);
	int mem = open("/proc/meminfo", O_RDONLY);
	int loadavg = open("/proc/loadavg", O_RDONLY);
	char temp[200];
	char* temp_ptr;
	int check = 0;
	int numOfCores;
	char model[200];
	int numMem;
	float loadavg1, loadavg5, loadavg15;
	
	while(check != EOF) {
		check = ReadTextLine(cpu, temp, 200);
		temp_ptr = strstr(temp, "cpu cores");
		if(temp_ptr != NULL) {
			//printf("%s\n", temp_ptr);
			temp_ptr = strtok(temp_ptr, " ");
			//if(temp_ptr != NULL) printf("%s\n", temp_ptr);
			temp_ptr = strtok(NULL, " ");
			temp_ptr = strtok(NULL, " ");
			if(temp_ptr != NULL) {
				sscanf(temp_ptr, "%d", &numOfCores);
				printf("# of processor cores = %d\n",numOfCores);
			}
			break;
		}
		temp_ptr = strstr(temp, "model name");
		if(temp_ptr != NULL) {
			temp_ptr = strtok(temp_ptr, " ");
			temp_ptr = strtok(NULL, " ");
			temp_ptr = strtok(NULL, "\0");
			if(temp_ptr != NULL){
				//sscanf(temp_ptr, "%s", model);
				strcpy(model,temp_ptr);
			}
		}
	}
	printf("CPU model = %s\n", model);
	close(cpu);

	while(check != EOF) {
		check = ReadTextLine(mem, temp, 200);
		temp_ptr = strstr(temp, "MemTotal");
		if(temp_ptr != NULL) {
			temp_ptr = strtok(temp_ptr, " ");
			//temp_ptr = strtok(NULL, " ");
			temp_ptr = strtok(NULL, " ");
			if(temp_ptr != NULL) {
				sscanf(temp_ptr, "%d", &numMem);
				printf("MemTotal = %d\n", numMem);
			}
			break;
		}
	}
	close(mem);

	while(check != EOF) {
		check = ReadTextLine(loadavg, temp, 200);
		temp_ptr = temp;
		if(temp != NULL) {
			temp_ptr = strtok(temp_ptr, " ");
			//printf("%s\n", temp_ptr);
			sscanf(temp_ptr, "%f", &loadavg1);
			temp_ptr = strtok(NULL, " ");
			sscanf(temp_ptr, "%f", &loadavg5);
			temp_ptr = strtok(NULL, " ");
			sscanf(temp_ptr, "%f", &loadavg15);
			
			printf("loadavg1 = %f, loadavg5 = %f, loadavg15 = %f\n", loadavg1, loadavg5, loadavg15);
			
			break;
		}
	}
	//sscanf(temp, "%d", &numOfCores);
	//printf("\n\n%s\n\n", temp);
	//printf("# of processor cores = %d\n", numOfCores);
	close(loadavg);
	return 0;
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
ㄴ
	return ret;
}
