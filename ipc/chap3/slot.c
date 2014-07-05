#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
int main( int argc, char* argv[]){
	int i,msgid;
	struct msqid_ds ds;
	struct ipc_perm * perm;
	for(i=0;i<10;i++){
		msgid=msgget(IPC_PRIVATE,0);
		printf("the msgid=%d",msgid);
		msgctl(msgid,IPC_STAT,&ds);
		perm=&(ds.msg_perm);
//		printf("key=%d,uid=%d,gid=%d,cuid=%d,cgid=%d,mode=%d,seq=%d\n",
///		perm->uid,perm->gid,perm->cuid,perm->cgid,perm->mode,perm->__seq);
		printf("  __seq=%d\n",perm->__seq);
		msgctl(msgid,IPC_RMID,0);
	}
	exit(0);

}
