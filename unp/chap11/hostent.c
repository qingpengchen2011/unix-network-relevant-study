#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>



int main(int argc,char* argv[]){
	
	struct hostent * ent;
	char** paliase;
	char** addrlist;
	char*  pname;
	char buf[48];
	while(--argc>0){
	
		pname=*++argv;
		if((ent=gethostbyname(pname))==NULL){
			fprintf(stderr,"error occur:%s\n",hstrerror(h_errno));
			continue;
		}	
		
		fprintf(stderr,"the official name:\n");
		fprintf(stderr,"	%s\n",ent->h_name);
		fprintf(stderr,"alias:\n");		
		paliase=ent->h_aliases;
		while(*paliase!=NULL){
			fprintf(stderr,"	%s\n",*paliase);
			paliase++;
		}
		fprintf(stderr,"addresses:\n");
		addrlist=ent->h_addr_list;
		while(*addrlist!=NULL){
			fprintf(stderr,"	%s\n",inet_ntop(AF_INET,*addrlist,buf,48));
			addrlist++;
		}
	
	}

	return 0;

}
