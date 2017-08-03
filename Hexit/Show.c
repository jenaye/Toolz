#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Show.h"

void showDefaultOutput(unsigned char *content) {
    int compteur = 0;
    for (int i = 0; i < strlen(content) ; i+=16) { //On affiche 16 charactère par ligne
        printf("%08x:\t", i); //colonne 1

        for (int j = 0; j < 16; j++) { //colonne 2
            unsigned char chr = content[i+j];


            if (j%2 == 0) {
                printf(" ");
            }

            printf("%02x",(unsigned) content[i+j]);
        }
        printf("\t");

        for (int k = 0; k < 16; k++) { //colonne 3
            unsigned char ch = content[i+k];

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
        "-h  : \t\t Show this help.\n"
        "-r  :\t\t totally reverse the input.\n"
        "-l  :\t\t Flip input in little endian.\n"
        "-f [fichier] :\t Specify a file to take input from. Default is from stdin.\n"
        "-i [input type] : Specify input type.\n\t\tValid input types are :\n\t\t- hexstring (with or  without 0x)\n\t\t- hexcode (hexstring with \\x)\n\t\t- base 64 / 32\n\t\t- default is raw.\n"
        "-o  [output type]: Specify output type. Possible arguments are the same as input type.\n"
    );
}
