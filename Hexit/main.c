#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 128



/* Prototypes */
char *readStreamFromStdin();
char *readStreamFromFile(FILE *fp);
void showHelp();
void showDefaultOutput();

/*Fonctions*/

void showDefaultOutput(char *content) {
    int compteur = 0;
    for (int i = 0; i < strlen(content) ; i+=16) { //On affiche 16 charactère par ligne
        printf("%08x:\t", i); //colonne 1

        for (int j = 0; j < 16; j++) { //colonne 2
            char chr = content[i+j];


            if (j%2 == 0) {
                printf(" ");
            }

            printf("%02x", content[i+j]);
        }
        printf("\t");

        for (int k = 0; k < 16; k++) { //colonne 3
            char ch = content[i+k];

            if (ch < 0x20 || ch > 0x7E) {
                printf(".");
            } else {
                printf("%c", ch);
            }
        }
        printf("\n");
    }
}





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
        if (c == EOF) {
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
    content[size] = '\0';
    fclose(fp);
    return content;
}



/* Main */
int main(int argc, char *argv[]) {

    /* Declarations*/
    char *content = NULL;
    bool littleEndian = false;
    bool reverse = false;
    bool help = false;
    int file = -1;
    int input = -1;
    int output = -1;

    /* Parsing des arguments */
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

        } else if ((!strcmp(argv[index], "-o")) || (!strcmp(argv[index], "--output"))) {
            output = index;
            break;

        } else if ((!strcmp(argv[index], "-i")) || (!strcmp(argv[index], "--input"))) {
            input = index;
            break;

        } else {
            printf("Unrecognized option %s.\n", argv[index]);
            exit(1);
        }
    }

    /* Interpretations en fonctions des arguments */

    if (help) {
        showHelp();
        exit(0);
    }

    /* Recuperation du contenu a traité */
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

    /* Traitement du contenu  en fonction de l'input */

    /*Traitement du contenu en fonction des arguments */

    /* Affichage au format d'output  */

    if (output = -1 || argv[output+1] == "default") {
        showDefaultOutput(content);
    }

    printf("TheEnd\n");
    free(content);
}


/* TODO :*/
/* 0: Fix showDefaultOutput */
/* 1: Modulariser le code */
/* 2: Input en mode \x\x / base64 / base32 */
/* 3: Output en mode \x\x / base64 / base32 */
/* 4: Crypto de base ? (cesar/xor/vigenere) */
/* 5: MiddleEndian */
/* 6: Selecteur de ligne/colonne */

