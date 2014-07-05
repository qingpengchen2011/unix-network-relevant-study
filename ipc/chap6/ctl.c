#include "comm.h"

#define SVMSG_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ) 


int main(int argc,char* argv[]){
	int msgid;
	struct msgbuf msg;
	struct msqid_ds ds;		
	msgid=msgget(IPC_PRIVATE,SVMSG_MODE|IPC_CREAT);
	if(msgid==-1){
		perror("msgget");
		exit(-1);
	}
	msg.mtype=1;
	msg.mtext[0]='Y';
	msgsnd(msgid,&msg,1,0);
			
	msgctl(msgid,IPC_STAT,&ds);
	printf("read-write:%03o,cbytes=%lu,qnum=%lu,qbytes=%lu\n",ds.msg_perm.mode,ds.__msg_cbytes,ds.msg_qnum,ds.msg_qbytes);
	system("ipcs -q");
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
}
