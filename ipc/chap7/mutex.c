#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define UPHEAD 1000000
#define NRTHREAD 5
void* add_routine(void*);

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int val;


int main(int argc, char* argv[]){
	pthread_t tid[NRTHREAD]; 
	int contri[NRTHREAD];
	int i; 
	for(i=0;i<NRTHREAD;i++){
		pthread_create(&tid[i],NULL,add_routine,&contri[i]);	
	}	
	for(i=0;i<NRTHREAD;i++){
		pthread_join(tid[i],NULL);
		printf("thread %d contri %d\n",i,contri[i]);
	}
	printf("add is over:%d\n",val);	
	return 0;
}

void* add_routine(void* arg){
	int* c=(int*)arg;
	*c=0;
	while(1){
		pthread_mutex_lock(&mutex);
		if(val>=UPHEAD){
			pthread_mutex_unlock(&mutex);
			break;
		}
		val++;
		(*c)++;
		pthread_mutex_unlock(&mutex);
		
	}		
}
