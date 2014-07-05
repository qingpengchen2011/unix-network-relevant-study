#include <stdio.h>
#include <shadow.h>


int main(int argc,char* argv[]){
	struct spwd* user;
	setspent();
	while((user=getspent())!=NULL){
		printf("loginname:%s,password:%s\n",user->sp_namp,user->sp_pwdp);
	}
	endspent();
	user=getspnam("linuxmin");	
	if(user!=NULL)
		printf("loginname:%s,password:%s\n",user->sp_namp,user->sp_pwdp);
	printf("......\n");
	return 0;
}
	
