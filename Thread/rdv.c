#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <semaphore.h>

#define TXT "longtemps je me suis couché de bonne heure"
#define PIN "pin"
#define PON "pon"
#define NB_THREAD 4

sem_t sem1, sem2;

void a(int i) {
    sleep(1);
    printf("a%d\n", i);
    sleep(1);
}

void b(int i) {
    sleep(1);
    printf("b%d\n", i);
    sleep(1);
}

void *p1(void *arg) {
    assert(arg == NULL);
    a(1);
    assert(sem_post(&sem2) == 0);
    assert(sem_wait(&sem1) == 0);
    b(1);
    return NULL;
}

void *p2(void *arg) {
    assert(arg == NULL);
    a(2);
    assert(sem_post(&sem1) == 0);
    assert(sem_wait(&sem2) == 0);
    b(2);
    return NULL;
}

struct str{
    char* txt;
};

void* display(void* arg){
    struct str *resu;
    resu = arg;
    printf("%s \n",resu->txt);
    return NULL;
}

int main() {
}