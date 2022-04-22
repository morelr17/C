#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <semaphore.h>

#define TXT1 "Pin "
#define TXT2 "Pon "

sem_t sem1;
sem_t sem2;

struct str {
    char* res;
};

void* display1(){
    for (int i=0;i<2;i++){ 
        sem_wait(&sem1);
        printf("%s \n",TXT1);
        sem_post(&sem2);
    }
        return NULL;
}

void* display2(){
    sem_wait(&sem2);
    printf("%s \n",TXT2);
    sem_post(&sem1);
    return NULL;
}

int main() {
    pthread_t t[4];
    sem_init(&sem1,0,1);
    sem_init(&sem2,0,0);
    
    
    pthread_create(t+0,NULL,display1,NULL);
    pthread_create(t+1,NULL,display2,NULL);
    

    for(int j=0;j<2;j++){
        pthread_join(t[j],NULL);
    }
    
    return 0;



}
