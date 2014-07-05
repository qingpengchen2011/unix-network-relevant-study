#include <stdio.h>
#include <pwd.h>

int main(int argc,char* argv[]){
	
	struct passwd* user;
	setpwent();
	while((user=getpwent())!=NULL){
		printf("%s\n",user->pw_name);
	}
	endpwent();	

	user=getpwnam("linuxmin");
	printf("name:%s,passwd:%s,uid:%d,gid:%d,userinfo:%s,home:%s,shell:%s\n",user->pw_name,user->pw_passwd,user->pw_uid,user->pw_gid,user->pw_gecos,user->pw_dir,user->pw_shell);
	return 0;



}
