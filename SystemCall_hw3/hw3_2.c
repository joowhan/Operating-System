#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <sys/sysinfo.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argv[1] == NULL){
		struct utsname un;
		struct sysinfo info;

		printf("User and Process info:\n");
		printf("\tgetuid() = %d\n", getuid());
		printf("\tgetpid() = %d\n", getpid());
		printf("\tgetppid() = %d\n\n", getppid());
		
		printf("Kernel info:\n");
		uname(&un);
		
		printf("\tsysname = %s\n", un.sysname);
		printf("\tnodename = %s\n", un.nodename);
		printf("\trelease = %s\n", un.release);
		printf("\tversion = %s\n", un.version);
		printf("\tmachine = %s\n\n", un.machine);
		
		printf("System Info:\n");
		sysinfo(&info);

		printf("\tuptime = %ld\n", info.uptime);
		printf("\ttotalram = %lu\n", info.totalram);
		printf("\tfreeram = %lu\n", info.freeram);
		printf("\tprocs = %d\n\n", info.procs);

	}
	else{
		int r=0;
		int w=0;
		int ex=0;
		if(0==access(argv[1], F_OK)){
			printf("Permission of file %s\n", argv[1]);
			if(0==access(argv[1], R_OK)){
				r++;
				printf("\tpermission to read: %d\n", r);
			}

			if(0==access(argv[1], W_OK)){
				w++;
				printf("\tpermission to write: %d\n", w);
			}
			if(0==access(argv[1], X_OK)){
				ex++;
				printf("\tpermission to execute: %d\n\n", ex);
			}
			struct stat sb;
			if(stat(argv[1], &sb)== -1) return 1;

			printf("stat of file %s\n", argv[1]);

			printf("\tst_dev = %ld\n",(long) sb.st_dev);
			printf("\tst_ino = %ld\n",(long) sb.st_ino);
			printf("\tst_mode = %o (octal)\n", sb.st_mode);
			printf("\tst_uid = %ld\n", (long) sb.st_uid);
			printf("\tst_gid = %ld\n", (long) sb.st_gid);
			printf("\tst_size = %lld\n", (long long) sb.st_size);

			struct tm *tm = localtime(&sb.st_atime);
			printf("\tst_atime = %d/%d/%d %d:%d:%d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
			struct tm *tm1 = localtime(&sb.st_mtime);
			printf("\tst_mtime = %d/%d/%d %d:%d:%d\n", tm1->tm_year+1900, tm1->tm_mon+1, tm1->tm_mday, tm1->tm_hour, tm1->tm_min, tm1->tm_sec);
			struct tm *tm2 = localtime(&sb.st_ctime);
			printf("\tst_ctime = %d/%d/%d %d:%d:%d\n", tm2->tm_year+1900, tm2->tm_mon+1, tm2->tm_mday, tm2->tm_hour, tm2->tm_min, tm2->tm_sec);
		}
	}
}
