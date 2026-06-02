#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

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
