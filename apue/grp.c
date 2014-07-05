#include <stdio.h>
#include <grp.h>

int main(int argc,char* agrv[]){
	struct group* gp;
	char** members;
	gp=getgrnam("linuxmin");
	printf("groupname:%s,grouppassword:%s,guid:%d,g_members:\n",gp->gr_name,gp->gr_passwd,gp->gr_gid);
	members=gp->gr_mem;
	//while(*members!=NULL){

		printf("%s\n",**members);
		members++;
//	}
	printf("...\n");
	return 0;



}
