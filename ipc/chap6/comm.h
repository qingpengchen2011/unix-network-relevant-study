#ifndef COMM_H
#define COMM_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

struct msgbuf{
	long mtype;
	char mtext[1];
};

#define SVMSG_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ) 


#endif

