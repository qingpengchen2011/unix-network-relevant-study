#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

int main(int argc,char* argv[]){
	mqd_t mqd;
	int r;
	int len;
	int prio;
	void* ptr;
	mqd=mq_open(argv[1],O_WRONLY);
	if(mqd==-1){
		perror("mq_open");
		exit(-1);
	}
	len=atoi(argv[2]);
	prio=atoi(argv[3]);
	ptr=malloc(len);
	r=mq_send(mqd,ptr,len,prio);
	if(r==-1){
		perror("mq_send");
		exit(0);
	}
	printf("%d len sent in %d prio\n",len,prio);
	mq_close(mqd);
	return 0;
}	
