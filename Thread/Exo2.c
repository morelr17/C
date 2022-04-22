#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <semaphore.h>

#define TXT "longtemps je me suis couché de bonne heure"

sem_t sem;


void* display(){
    sem_wait(&sem);
    printf("%s \n",TXT);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t thread[4];
    sem_init(&sem,0,1);
    int i;

    for(i=0;i<4;i++){
      pthread_create(thread+i,NULL,display,NULL);
        }
    for (int j=0;j<4;j++){
        pthread_join(thread[j],NULL);
    }
    
    return 0;


}
