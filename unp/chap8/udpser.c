#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void do_ser(int sockfd,struct sockaddr* cliaddr,int len);


int main( int argc , char* argv[]){
	struct sockaddr_in cliaddr,seraddr;
	int udpfd;
	
	udpfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&cliaddr,sizeof(cliaddr));
	bzero(&seraddr,sizeof(seraddr));
	
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(udpfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	fprintf(stderr,"blocking in recvfrom\n");
	do_ser(udpfd,(struct sockaddr*) &cliaddr,sizeof(cliaddr));	

}

void do_ser(int sockfd,struct sockaddr* cliaddr,int len){
	time_t tv;
	int n,nlen;
	char buffer[2048];
	char cont[54];	
	struct sockaddr_in* clisin;
	struct sockaddr loaddr
	for(;;){
		time(&tv);
		n=recvfrom(sockfd,buffer,2048,0,loaddr,&nlen);	
		buffer[n]='\0';
		clisin=(struct sockaddr_in *)loaddr;
		inet_ntop(AF_INET,&(clisin->sin_addr),cont,54);
		fprintf(stderr,"cli addr struct len is %d,cli addr is %s,port is %d\n",nlen,cont,ntohs(clisin->sin_port));
		fprintf(stderr,"recv from cli: %s\n",buffer);
		//strcat(buffer,ctime(&tv));
		fprintf(stderr,"contnet sent to cli:%s\n",buffer);
		sendto(sockfd,buffer,strlen(buffer),0,cliaddr,nlen);		
	}
	

}
