/*
Ngelola genre lagu
Display Genre
Show Songs By Genre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct judulLagu
{
    char lagu[100];
    struct judulLagu *next;
}judulLagu;

typedef struct nodeGenre
{
    char genre[20];
    judulLagu *headLagu;
    
    struct nodeGenre *kiri;
    struct nodeGenre *kanan    
}nodeGenre;

nodeGenre *root = NULL;


nodeGenre *untukGenre(char genre[]){
    nodeGenre *iniGenre = (nodeGenre *) malloc(sizeof(nodeGenre));

    strcpy(iniGenre->genre, genre);
    iniGenre->headLagu = NULL;
    iniGenre->kanan = NULL;
    iniGenre->kiri = NULL;

    return iniGenre;
}


int main(){}