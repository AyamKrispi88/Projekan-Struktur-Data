#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "utility.c"
#include "user.c"
#include "kelolaMusik.c"
#include "playlist.c"
#include "queuePlayLagu.c"
#include "playedHistory.c"
#include "genrePengelompokkanLagu.c"
#include "rekomendLagu.c"

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

int main(){
    int pil;
    do
    {
        printf("Menu Pilihan: ");
        printf("");
        scanf("%d", &pil);
        switch (pil)
        {
        case 1:{
            /* code */
            break;
        }
        default:{
            break;
        }
        } 
    } while (pil != 5);
    
}
