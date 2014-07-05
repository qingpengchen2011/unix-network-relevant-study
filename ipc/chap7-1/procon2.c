#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXNITMES 10000000
#define MAXNTHREADS 100
int nitems;
struct {
	pthread_mutex_t mutex;
	int buff[MAXNITMES];
	int nput;
	int nval;
} shared={
	PTHREAD_MUTEX_INITIALIZER
};
void consume_wait(int i){
	for(;;){
		pthread_mutex_lock(&shared.mutex);
		if(i<shared.nput){
			pthread_mutex_unlock(&shared.mutex);	
			return;
		}
		pthread_mutex_unlock(&shared.mutex);
	}
}
void* produce(void*),*consume(void*);
int min(int a,int b){
	return (a>=b)?b:a;
}
int main(int argc,char* argv[]){
   int i,nthreads,count[MAXNTHREADS];
   pthread_t tid_produce[MAXNTHREADS],tid_consume;
   nitems=min(atoi(argv[1]),MAXNITMES);
   nthreads=min(atoi(argv[2]),MAXNTHREADS);
   clock_t st,ed;
   double gap;
   st=clock();
   for(i=0;i<nthreads;i++){
	count[i]=0;
	pthread_create(&tid_produce[i],NULL,produce,&count[i]);
   }
   
   pthread_create(&tid_consume,NULL,consume,NULL);
	
   for(i=0;i<nthreads;i++){
	pthread_join(tid_produce[i],NULL);
    	printf("count[%d]=%d\n",i,count[i]);
   }	
   pthread_join(tid_consume,NULL);
   ed=clock();
   gap=(double)(ed-st);
   printf("gap time %f\n",gap/CLOCKS_PER_SEC);   
    return 0;
}

void* produce(void* arg){
	for(;;){
		pthread_mutex_lock(&shared.mutex);
    		if(shared.nput>=nitems){
			pthread_mutex_unlock(&shared.mutex);
			break;
		}
		shared.buff[shared.nput]=shared.nval;
		shared.nval++;
		shared.nput++;	
		pthread_mutex_unlock(&shared.mutex);
		*((int*)arg)+=1;

	}
}
void* consume(void* arg){
	int i;
	for(i=0;i<nitems;i++){
		consume_wait(i);
		if(shared.buff[i]!=i)
			printf("buff[%d]=%d\n",i,shared.buff[i]);
	}	
}
