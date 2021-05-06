#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH 256

int FindFile(char *start_dir, char *target, char *path);

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage %s <start_dir> <target_file> \n", argv[0]);
		return 0;
	}
	char *start_dir = argv[1];
	char *target = argv[2];
	char path[MAX_PATH] = "";
	int ret = FindFile(start_dir, target, path);
	//printf("%s\n", target);
	if(ret)
		printf("path = %s", path);
	else
		printf("Cannot find %s", target);
	
	return 0;
}

int FindFile(char *start_dir, char *target, char *path){
	// if name is . or .. then, skip ?
	//ex) start_dir = ../../HW#2 then move directory
	
	DIR *dp;
	struct dirent *dir;
	char temp[MAX_PATH] = "";
	int result = 0;
	dp = opendir(start_dir);
	while((dir = readdir(dp))!=NULL){
		//find tartget?
		if(strcmp(target, dir->d_name) == 0 ){
			path = strcat(getcwd(path, MAX_PATH), "/");
			path = strcat(path, target);
			return 1;
		}
	}
	rewindir(dp);
	while((dir = readdir(dp))!=NULL){
		
		if(dir->d_type == 0x04){ // is folder?
			//is it target?
			//then, call Findfile(new start_dir)
			//Enter the folder
			start_dir = dir->d_name;
			printf("%s\n", start_dir);
			result = FindFile(start_dir, target, path);
			if(result) return 1;
		}
	}
	closedir(dp);
	return 0;
	 
}
