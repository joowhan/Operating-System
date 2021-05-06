#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	float wait;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	wait = atof(argv[1]);
	struct timeval startTime, endTime, diffTime;
	//float diffTime;

	printf("current date: %d /%d /%d \n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
	printf("current time: %d: %d :%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	printf("waiting for %f sec using usleep()\n", wait);
	gettimeofday(&startTime, NULL);
	printf("start_time: (%ld %ld) %d: %d :%d\n",startTime.tv_sec, startTime.tv_usec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	usleep(wait*1000000);
	gettimeofday(&endTime, NULL);
	//diffTime = (endTime.tv_sec - startTime.tv_sec) +(( endTime.tv_usec - startTime.tv_usec)/1000000);
	t = startTime.tv_sec;
	tm = *localtime(&t);
	
	//printf("start_time: (%d %d) %d: %d :%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	
	t = endTime.tv_sec;
	tm = *localtime(&t);
	printf("end_time: (%ld %ld) %d: %d :%d\n",endTime.tv_sec, endTime.tv_usec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	if(endTime.tv_sec <startTime.tv_sec){
		endTime.tv_sec -=1;
		endTime.tv_usec +=1000000;
	}
	//diffTime = (endTime.tv_sec - startTime.tv_sec) +(( endTime.tv_usec - startTime.tv_usec)/1000000);
	diffTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
	diffTime.tv_usec = endTime.tv_usec - startTime.tv_usec;
	printf("elapsed time: %ld.%0.6ld sec\n", diffTime.tv_sec, diffTime.tv_usec);
}
