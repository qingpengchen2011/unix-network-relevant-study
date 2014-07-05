#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char buffer[1024];
	int n,fd,len;
	
	printf("enter the path:\n");
	fgets(buffer,1024,stdin);
	printf("read from tty is %s",buffer);
	len=strlen(buffer);
	if(buffer[len-1]=='\n')
		buffer[len-1]='\0';
	
//	printf("read from tty is %s",buffer);
	if((fd=open(buffer,O_RDWR))==-1){
		perror("open");
		exit(0);
		
	}
	while((n=read(fd,buffer,1024))>0){
		buffer[n]='\0';
		fputs(buffer,stdout);
	}
	return 0;
}
	
