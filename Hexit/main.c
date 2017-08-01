#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 128

char *readStreamFromStdin();
char *readStreamFromFile(FILE *fp);
void showHelp();



void showHelp() {
    printf("\t<--- Hexit help --->\n"
        "-h, --help :\t\t Show this help.\n"
        "-r , --reverse :\t totally reverse the input.\n"
        "-l, --littleendian :\t Flip input in little endian.\n"
        "-f, --file :\t\t Specify a file to take input from. Default is from stdin.\n"
    );
}


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
    bool littleEndian = false;
    bool reverse = false;
    bool help = false;
    int file = -1;
    int mode = -1;

    for (int index = 1; index < argc && argv[index][0] == '-'; index++) {
        if ((!strcmp(argv[index], "-l")) || (!strcmp(argv[index], "--littleendian"))) {
            littleEndian = true;
            break;

        } else if ((!strcmp(argv[index], "-r")) || (!strcmp(argv[index], "--reverse"))) {
            reverse = true;
            break;
        } else if ((!strcmp(argv[index], "-h")) || (!strcmp(argv[index], "--help"))) {
            help = true;
        } else if  ((!strcmp(argv[index], "-f")) || (!strcmp(argv[index], "--file")))  {
            file = index;
            break;

        } else if ((!strcmp(argv[index], "-m")) || (!strcmp(argv[index], "--mode"))) {
            mode = index;
            break;
        } else {
            printf("Unrecognized option %s.\n", argv[index]);
            exit(1);
        }
    }

    if (help) {
        showHelp();
        exit(0);
    }



    if (file > -1) {
        FILE *fd = fopen(argv[file+1], "r");
        if (fd == NULL) {
            printf("Impossible to open %s.\n" , argv[file+1]);
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
