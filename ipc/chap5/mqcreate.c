#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#define QUE_NAME "/tmp/MQ/mqueue"
#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) 
int main(int argc,char* argv[]){ 
    mqd_t mqd; 
    struct mq_attr attr;
    bzero(&attr,sizeof(attr));
    attr.mq_maxmsg=atol(argv[2]);
    attr.mq_msgsize=atol(argv[3]);
    mqd=mq_open(argv[1],O_RDWR|O_CREAT,FILE_MODE,(attr.mq_maxmsg==0)?NULL:&attr);
    if(mqd==-1){
        fprintf(stderr,"mq_open:%s\n",strerror(errno));
	perror("perror:");
	exit(0);
    }
    return 0;
}
