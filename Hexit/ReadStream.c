#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ReadStream.h"



unsigned char *readStreamFromStdin() {
    unsigned char *content = malloc(SIZE);

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
        if (c == EOF) {
            c = '\0';
            break;
        }
    content[compteur] = c;
    compteur++;
    }

    return content;
}

unsigned char *readStreamFromFile(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    unsigned char *content = (unsigned char*) malloc(sizeof(char) * size);
    fread(content, 1, size, fp);
    content[size] = '\0';
    fclose(fp);
    return content;
}
