/*Ini buat mengelola seluruh lagunya, buat ngeshow data lagu dari file txt musiks aja si*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct kelolaMusik
{
    char judul[1000];
    char penyanyi[1000];

    struct kelolaMusik *depan; // --> next
    struct kelolaMusik *belakang; // double linked list --> prev
}kelolaMusik;

typedef struct dataMusik
{
    /* data */
}dataMusik;   

void laguData(){
    FILE *Musik;
    int lgu;
    Musik = fopen("lagu.txt", "r");
    while ((lgu = fgetc(Musik)) != EOF){
        printf("%s", lgu);
    }
    fclose(Musik);
}

void liat(){
    FILE *musik = fopen();
}