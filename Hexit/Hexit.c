#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ReadStream.h"
#include "Show.h"




int main(int argc, char *argv[]) {

    /* Declarations*/
    unsigned char *content = NULL;
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
/* 0: Fix showDefaultOutput (null bytes en trops) */
/* 1: Modulariser le code */
/* 2: Input en mode \x\x / base64 / base32 */
/* 3: Output en mode \x\x / base64 / base32 */
/* 4: Crypto de base ? (cesar/xor/vigenere) */
/* 5: MiddleEndian */
/* 6: Selecteur de ligne/colonne */
