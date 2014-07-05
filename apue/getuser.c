#include <unistd.h>
#include <stdio.h>

int main( int argc,char* argv[]){
	
	char* user;
	user=getlogin();
	puts(user);
	return 0;
}
