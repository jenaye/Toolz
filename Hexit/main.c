#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 128



char *readStreamFromStdin() {
    char *content = malloc(SIZE);

    if (content == NULL) {
        printf("Unable to malloc.\n");
        exit(1);
    }


    unsigned int compteur = 0;
    unsigned int tailleActuelle = SIZE;

    while(1){
        if (compteur >= tailleActuelle) {
            tailleActuelle += SIZE;
            content = realloc(content, tailleActuelle);

            if  (content == NULL) {
                printf("Unable to realloc.\n");
                exit(1);
            }
        }

        char c = getc(stdin);
        if (c == EOF || c == '\n') {
            c = '\0';
            break;
        }
    content[compteur] = c;
    compteur++;
    }

    return content;
}


char *readStreamFromFile(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    char *content = (char*) malloc(sizeof(char) * size);
    fread(content, 1, size, fp);

    fclose(fp);
    return content;
}


int main(int argc, char *argv[]) {

    char *content = NULL;
    bool l = false;
    bool r = false;
    int f = -1;


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
            printf("Impossible to open %s.\n" , argv[f+1]);
            exit(1);
        }
        content = readStreamFromFile(fd);

    } else {
        content = readStreamFromStdin();
    }


    printf("Content : %s\n", content);
    free(content);
}





/*
 -h = l'aide
 -l = little endian
 -f = on passe un fichier a lire
 -o = fichier d'output


 */
