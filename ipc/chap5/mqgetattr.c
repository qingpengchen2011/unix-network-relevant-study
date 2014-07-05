#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
	int r;
	mqd_t mqd;
	struct mq_attr attr;
	mqd=mq_open(argv[1],O_RDONLY);
	if(mqd==-1){
		fprintf(stderr,"mq_open:%s\n",strerror(errno));
		exit(-1);
	}
	r=mq_getattr(mqd,&attr);
	if(r==-1){
		fprintf(stderr,"mq_getattr:%s\n",strerror(errno));
		exit(-1);
	}
	printf("mq_flags:%ld,mq_maxmsg:%ld,mq_msgsize:%ld,mq_curmsgs:%ld\n",attr.mq_flags,attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);
	return 0;
}
		
	
