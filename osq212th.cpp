#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>


/* yara adel hassan mohamed 19100683 */

#define THREAD_NUM 8
int buffer[10];
int counter=0;
sem_t s,n,semFull ; 



void* producer(void* args){
        FILE * fp;
        fp = fopen ("produceractivity.txt", "w"); 
        int i ;  
        
	for(i=0;i<10000;i++){
        sem_wait(&semFull);
        sem_wait(&s);
        

	int x=rand()%1000;
        
	buffer[counter]=x;
	counter++;
	printf("produced %d\n",x);
 fprintf(fp, "producer produced item number %d with value %d %s",counter, x,"\n");
	sem_post(&s); 
	sem_post(&n); 
	//printf("skipped %d\n",x);
		
	}
        fclose(fp);	
	return 0;
        
	}
	
void* consumer(void* args){
        FILE * fp;
        fp = fopen ("consumeractivity.txt", "w");  
	int i ; 
	for(i=0;i<10000;i++){
         sem_wait(&n) ; 
         sem_wait(&s);
		
	int y=buffer[counter-1];
	counter--;
	printf("got %d\n",y);
        fprintf(fp, "consumer consumed item number %d with value %d %s",counter, y,"\n");
	sem_post(&s);
        sem_post(&semFull);  
	}
        fclose(fp);	
	return 0;

	
	}

int main(int argc, char *argv[]) {
	sem_init(&s, 0, 1);
        sem_init(&n, 0, 0);
        sem_init(&semFull, 0, 10);
	pthread_t th[THREAD_NUM];
	
	int i;
         
	for(i=0;i<THREAD_NUM;i++){
		if(i%2==0){
		
		if(pthread_create(&th[i],NULL,producer,NULL)!=0){
			perror("failed to create thread");
		}
	}	else{
			if(pthread_create(&th[i],NULL,consumer,NULL)!=0){
				perror("failed to create thread");
			}
		}
	}
       for (i=0 ; i<THREAD_NUM;i++){
	 pthread_join(th[i],NULL);
      
	}	
	return 0;
}
