#include <stdio.h>
#include <string.h>
#define MAX 1024
int main(int argc ,char* argv[]){
	FILE* fd;
	char buffer[MAX],command[MAX];
	int n;
	printf("please enter the file path:\n");
	fgets(buffer,MAX,stdin);
	n=strlen(buffer);
	if(buffer[n-1]=='\n')
		buffer[n-1]='\0';
	snprintf(command,MAX,"cat %s",buffer);
	fd=popen(command,"r");
	while(fgets(buffer,MAX,fd)!=NULL){
		fputs(buffer,stdout);
	}
	
	return 0;
	
}
