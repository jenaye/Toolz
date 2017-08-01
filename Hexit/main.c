#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 128





void readStream(FILE *fp, char* data){
    int c = EOF;
    unsigned int actualSize = SIZE;
    unsigned int i = 0;
    while (( c = getchar()  ) != '\n' && c != EOF){
        data[i++] = (char)c;

        if (i = actualSize) {
            actualSize = i + SIZE;
            data = realloc(data, actualSize);
        }
    }
    fclose(fp);
}



int main(int argc, char *argv[]) {

    bool l = false;
    bool r = false;
    int f = -1;
    char *content = malloc(SIZE);

    if (content == NULL) {
       printf("Memory allocation failed.\n");
       exit(1);
    }

    for (int index = 1; index < argc && argv[index][0] == '-'; index++) {
        if (!strcmp(argv[index], "-l")) {
            l = true;
            printf("Found -l option!\n");
            break;

        } else if (!strcmp(argv[index], "-r")) {
            r = true;
            printf("Found -r option!\n");
            break;
        } else if  (!strcmp(argv[index], "-f")) {
            f = index;
            printf("Found -f options !\n");
            break;
        } else {
            printf("Unrecognized option %s.\n", argv[index]);
            exit(1);
        }
    }

    if (f != -1) {
        FILE *fd = fopen(argv[f+1], "r");
        if (fd == NULL) {
            printf("Impossible de lire le fichier %s.\n" , argv[f+1]);
            exit(1);
        }
        readStream(fd, content);

    }


    printf("Content : %s\n", content);
    free(content);
}





/*
 -h = l'aide
 -l = little endian
 -r = reverse complet
 -f = on passe un fichier a lire
 -o = fichier d'output


 */
