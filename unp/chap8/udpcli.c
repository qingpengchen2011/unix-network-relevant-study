#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>


void do_cli(int socket, struct sockaddr* ,int len);

int main( int argc , char* argv[]){
	int udpfd;
	struct sockaddr_in seraddr;
	
	udpfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr);
	fprintf(stderr,"waiting inputs..\n");
	do_cli(udpfd,(struct sockaddr*)&seraddr,sizeof(seraddr));	
	
	return 0;
	

}

void do_cli(int sockfd, struct sockaddr* seraddr ,int len){
	char buffer[1024];
	int n;
	while(fgets(buffer,sizeof(buffer),stdin)!=NULL){
		fprintf(stderr,"read from tty:%s\n",buffer);
		sendto(sockfd,buffer,strlen(buffer),0,seraddr,len);
		n=recvfrom(sockfd,buffer,1024,0,NULL,NULL);
		buffer[n]='\0';
		fprintf(stderr,"recvfrom server content:%s\n",buffer);	
	}
}
