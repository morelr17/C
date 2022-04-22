#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

unsigned long compteur_gc(char *bloc, unsigned long taille) {
    unsigned long i, cptr = 0;

    for (i = 0; i < taille; i++)
        if (bloc[i] == 'G' || bloc[i] == 'C')
            cptr++;

    return cptr;
}

struct compteur_s{
    char * bloc ;
    unsigned long taille ;
    unsigned long res ; 
};

void * my_compteur_gc(void* arg) {
    struct compteur_s* s;
    s = arg ;
    s ->res = compteur_gc(s->bloc,s->taille);
    
    return (void *) s->res ;
}

int main(int argc, char *argv[]) {
    struct stat st;
    struct compteur_s s;
    struct timespec debut1, fin1;
    struct timespec debut2, fin2;
    int fd;
    int nb_thread = atoi(argv[2]);
    int lus;
    char *tampon;
    pthread_t thr[nb_thread];

    unsigned long cptr_thread = 0 ;
    unsigned long cptr = 0;
    off_t taille = 0;
    

    assert(argc > 1);

    /* Quelle taille ? */
    assert(stat(argv[1], &st) != -1);
    tampon = malloc(st.st_size);
    assert(tampon != NULL);

    /* Chargement en mémoire */
    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);
    while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0)
        taille += lus;
    assert(lus != -1);
    assert(taille == st.st_size);
    close(fd);

    /* Calcul proprement dit */
    assert(clock_gettime(CLOCK_MONOTONIC, &debut1) != -1);
    cptr = compteur_gc(tampon, taille);
    assert(clock_gettime(CLOCK_MONOTONIC, &fin1) != -1);
    printf("Mono Thread : \n \n");

    /* Affichage des résultats */
    printf("Nombres de GC:   %ld\n", cptr);
    printf("Taux de GC:      %lf\n", ((double) cptr) / ((double) taille));

    fin1.tv_sec  -= debut1.tv_sec;
    fin1.tv_nsec -= debut1.tv_nsec;
    if (fin1.tv_nsec < 0) {
        fin1.tv_sec--;
        fin1.tv_nsec += 1000000000;
    }
    printf("Durée de calcul: %ld.%09ld \n", fin1.tv_sec, fin1.tv_nsec);
    printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n \n");

    printf("Processus avec %d Thread : \n \n",nb_thread);

    assert(clock_gettime(CLOCK_MONOTONIC, &debut2) != -1);

    for (int i=0;i<nb_thread;i++){
        s.taille = taille/nb_thread ;
        s.bloc = tampon + s.taille*i;

        pthread_create(thr+i,NULL,my_compteur_gc,&s);
        pthread_join (thr[i],NULL);
        
        cptr_thread +=(unsigned long) s.res;
    }

    assert(clock_gettime(CLOCK_MONOTONIC, &fin2) != -1);

    /* Affichage des résultats */
    printf("Nombres de GC:   %ld\n", cptr_thread);
    printf("Taux de GC:      %lf\n", ((double) cptr_thread) / ((double) taille));

    

    fin2.tv_sec  -= debut2.tv_sec;
    fin2.tv_nsec -= debut2.tv_nsec;
    if (fin2.tv_nsec < 0) {
        fin2.tv_sec--;
        fin2.tv_nsec += 1000000000;
    }
    printf("Durée de calcul: %ld.%09ld\n", fin2.tv_sec, fin2.tv_nsec);
    printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n");

    return 0;
}

