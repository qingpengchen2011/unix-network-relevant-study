#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define SIZE 2048

void client(int readfd,int writefd);
void server(int readfd,int writefd);


int main(int argc, char* argv[]){
	int fd1[2],fd2[2];
	int cpid;	
	if(pipe(fd1)!=0){
		perror("pipe");
		exit(0);
	}
	
	if(pipe(fd2)!=0){
		perror("pipe");
		exit(0);
	}
	
	if((cpid=fork())==0){ //in child
		close(fd1[1]);
		close(fd2[0]);
		server(fd1[0],fd2[1]);
		return 0;
	}
	else if(cpid==-1){ // error happen
		perror("fork");
		exit(0);
	}
	else{ // in parent
		close(fd1[0]);
		close(fd2[1]);
		client(fd2[0],fd1[1]);
	}
	
	return 0;
}

void client(int readfd,int writefd){
	char buffer[SIZE];
	int n;
	printf("enter the path\n");
	gets(buffer);
	n=strlen(buffer);
	if(buffer[n-2]=='\n')
		buffer[n-2]='\0';
	printf("parent process read from tty:%s\n",buffer);
	write(writefd,buffer,n);
	printf("read data throught pie from child\n");	
	while((n=read(readfd,buffer,SIZE))>0){
		buffer[n-1]='\0';
		fputs(buffer,stdout);	
	}		
	puts("");
}

void server(int readfd,int writefd){
	char buffer[SIZE];
	int n,fd;
	if((n=read(readfd,buffer,SIZE))==-1){
		perror("child process read");
		exit(0);
	}
	buffer[n]='\0';
	printf("throught pipe read the path is %s\n",buffer);
	if((fd=open(buffer,O_RDONLY))==-1){
		printf("child process open\n");	
		snprintf(buffer+n,SIZE-n,"error:%s",strerror(errno));
		write(writefd,buffer,SIZE);
	}
	else{
		while((n=read(fd,buffer,SIZE))>0){
			write(writefd,buffer,n);
		}
	}
}
