#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
int main(int argc,char* argv[]){
	int r,prio;
	long n;
	mqd_t mqd;
	struct mq_attr attr;
	void* ptr;
	mqd=mq_open(argv[1],O_RDONLY);
	if(mqd==-1){
		perror("mq_open");
		exit(-1);
	}
	r=mq_getattr(mqd,&attr);
	if(r==-1){
		perror("mq_getattr");
		exit(-1);
	}
	ptr=malloc(attr.mq_msgsize);
	n=mq_receive(mqd,ptr,attr.mq_msgsize,&prio);
	printf("receive %ld bytes in %d prio\n",n,prio);
	mq_close(mqd);
	return 0;
}
