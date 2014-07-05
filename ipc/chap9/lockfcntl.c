#include <unistd.h>
#include <fcntl.h>
void my_lock(int fd){
	struct flock lock;
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	fcntl(fd,F_SETLKW,&lock);
	return;
}

void my_unlock(int fd){
	struct flock lock;
	lock.l_type=F_UNLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	fcntl(fd,F_SETLK,&lock);
	return;
	
}
