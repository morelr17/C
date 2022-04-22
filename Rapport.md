## Membres du binôme

- Romain Morel
- Nawfel Senoussi

---
# TP-Stat

## 1/Questions traitées:

### Exercice 5:

Nous avons créer le fichier test puis nous avons lancé la commande suivante:

```
stat test
```

et nous avons obtenu:

```
  File: test 
  Size: 31     	Blocks: 8         IO Block: 1048576 regular file
Device: 3bh/59d	Inode: 142097094   Links: 1
Access: (0644/-rw-r--r--)  Uid: (10387/  morelr)   Gid: ( 1320/ l3miage)
Access: 2021-09-17 08:24:04.606567668 +0200
Modify: 2021-09-17 08:24:26.386596886 +0200
Change: 2021-09-17 08:24:26.386596886 +0200
 Birth: -
```

### Exercice 6:

Nous avons lancé la commande suivante:

```
whatis stat
```
et nous avons obtenu:
```
stat (1)             - display file or file system status
stat (2)             - get file status
stat (3posix)        - get file status
```

### Exercice 7*:

- Le champs "Blocs" représente le nombre de bloc alloués 
- Le champs "Blocs d’E/S" représente la taille de bloc pour E/S

### Exercice 8:

A partir de 4097 le nombre de blocs augmente de 8.

Il augmente de 8 en 8 car c'est codé en hexadecimale.


### Exercice 9:
Pour créer le lien physique, nous avons lancé la commande suivante:
```
ln test test-hardlink
```

Pour créer le lien symbolique, nous avons lancé la commande suivante:
```
ln -s test test-symboliclink
```

Pour créer la copie, nous avons lancé la commande suivante:

```
cp test copy_test
```


### Exercice 10:

- Pour le fichier test, le lien physique ,le nombre de lien est le même et augmente en fonction du nombre de lien que nous créons.
En revanche la copie et lien symbolique n'évoluent pas en fonction du nombre de lien et reste à 1.

- Le lien physique et le fichier test possèdent le même numéro d’i-nœuds tandis que le lien symbolique et la copie possèdent des numéros différents.

- On retrouve le texte dans la copie et le lien physique.
Par contre on ne peut plus ouvrir le lien symbolique.

### Exercice 11 - 12:

Nous avons écrit le code suivant:

```
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>


int main(int argc, char *argv[])
       {
           struct stat stats;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(1);
           }

           if (lstat(argv[1], &stats) == -1) {
               perror("lstat");
               exit(1);
           }

           printf("ID du périphérique :                  [%lx,%lx]\n",
                (long) major(stats.st_dev), (long) minor(stats.st_dev));

           printf("Type de fichier:                      ");

           switch (stats.st_mode & S_IFMT) {
           case S_IFBLK:  printf("un périphérique en mode bloc\n");            break;
           case S_IFCHR:  printf("un péripherique en mode caractère\n");        break;
           case S_IFDIR:  printf("un répertoire\n");               break;
           case S_IFIFO:  printf("une FIFO/pipe\n");               break;
           case S_IFLNK:  printf("un lien symbolique \n");                 break;
           case S_IFREG:  printf("un fichier régulier\n");            break;
           case S_IFSOCK: printf("une socket\n");                  break;
           default:       printf("inconu ?\n");                break;
           }

           printf("Numéro d'inoeud:                      %ld\n", (long) stats.st_ino);

           printf("Mode:                                 %lo (octal)\n",
                   (unsigned long) stats.st_mode);

           printf("Nombre de liens physiques:            %ld\n", (long) stats.st_nlink);
           printf("UID et GID du propriétaire:           UID=%ld   GID=%ld\n",
                   (long) stats.st_uid, (long) stats.st_gid);

           printf("Taille du bloc poue E/S :             %ld bytes\n",
                   (long) stats.st_blksize);
           printf("Taille totale en octects:             %lld bytes\n",
                   (long long) stats.st_size);
           printf("Nombre de blocs de 512 octect alloués:%lld\n",
                   (long long) stats.st_blocks);

           printf("Heure dernier accès :                 %s", ctime(&stats.st_ctime));
           printf("Heure dernière modification :         %s", ctime(&stats.st_atime));
           printf("Heure dernier changement état :       %s", ctime(&stats.st_mtime));

           exit(0);
       }
```
et nous avons obtenu : 
```
senoussin@a10p8:~/Documents/pds-fs-morel-senoussi/stat$ ./stat Makefile
ID du périphérique :                  [0,3c]
Type de fichier:                      un fichier régulier
Numéro d'inoeud:                      52823009
Mode:                                 100644 (octal)
Nombre de liens physiques:            1
UID et GID du propriétaire:           UID=9907   GID=1320
Taille du bloc poue E/S :             1048576 bytes
Taille totale en octects:             161 bytes
Nombre de blocs de 512 octect alloués:8
Heure dernier accès :                 Mon Sep 27 14:35:06 2021
Heure dernière modification :         Mon Sep 27 14:35:06 2021
Heure dernier changement état :       Mon Sep 27 14:35:06 2021

```



### Exercice 13:
Nous avons ajouté le code suivant:
```
struct passwd *user = getpwuid(stats.st_uid);
            printf("Utilisateur :                         %s \n", user -> pw_gecos);
            
            struct group *groupe = getgrgid(stats.st_gid);
            printf("Groupe :                              %s \n", groupe -> gr_name);
```
et nous avons obtenu : 
```
./stat Makefile
ID du périphérique :                  [0,3c]
Type de fichier:                      un fichier régulier
Numéro d'inoeud:                      52823009
Mode:                                 100644 (octal)
Nombre de liens physiques:            1
UID et GID du propriétaire:           UID=9907   GID=1320
Taille du bloc poue E/S :             1048576 bytes
Taille totale en octects:             161 bytes
Nombre de blocs de 512 octect alloués:8
Heure dernier accès :                 Mon Sep 27 14:35:06 2021
Heure dernière modification :         Mon Sep 27 14:35:06 2021
Heure dernier changement état :       Mon Sep 27 14:35:06 2021
Utilisateur :                         Senoussi Nawfel 
Groupe :                              l3miage 
```




## 2/Questions non-traitées: 

## 3/Notions:

## 4/Compte-rendu

---
# TP-Performances

## 1/Questions traitées:

### Exercice 28:

#### 1)

Nous avons écrit le code suivant pour créer la commande stat:

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc,char *argv[]){

    if(argc != 3){
        printf("erreur d'argument");
        exit(1);
    }

    int sizetmp;
    sizetmp = atoi(argv[1]);

    int fd;
    if( (fd = open(argv[2], O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    char buffer[sizetmp];

    int readChar;
    while ( (readChar = read(fd,buffer,sizeof(buffer))) > 0) {
        write(0,buffer,readChar);
    }

    close(fd);
    exit(0);
}
```

#### 2)



## 2/Questions non-traitées: 

## 3/Notions:

## 4/Compte-rendu

