#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int main(){
	DIR *dp;
	struct dirent *dir;

	dp = opendir("/");

	while((dir = readdir(dp)) != NULL){
		if(dir->d_type == 0x04)
			printf("%s [directory]\n", dir->d_name);
		else 
			printf("%s\n", dir->d_name);
	}
	closedir(dp);
}
