#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "seqno"
#define LOOPNUM 3000000

#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH )
void my_lock(int),my_unlock(int);
int main(int argc,char* argv[]){
	int fd;
	pid_t pid;
	char buf[1024];
	int i,n,cnt;
	pid=getpid();
	fd=open(FILENAME,O_CREAT|O_RDWR,FILE_MODE);
	//snprintf(buf,sizeof(buf),"%ld",pid);
	//write(fd,buf,strlen(buf));
	for(i=0;i<LOOPNUM;i++){
		my_lock(fd);
		lseek(fd,0,SEEK_SET);
		n=read(fd,buf,sizeof(buf));
		buf[n]='\0';
		sscanf(buf,"%d",&cnt);
		//printf("arg=%s,pid=%ld,cnt=%d\n",argv[0],(long)pid,cnt);
		cnt++;
		snprintf(buf,sizeof(buf),"%d",cnt);
		lseek(fd,0,SEEK_SET);
		write(fd,buf,strlen(buf));
		my_unlock(fd);
	}
	return 0;

}
