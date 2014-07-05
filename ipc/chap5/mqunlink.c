#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[]){
	int r;
	r=mq_unlink(argv[1]);
	if(r==-1){
		fprintf(stderr,"mq_unlink:%s\n",strerror(errno));
		exit(-1);
	}
	return 0;
}
	
