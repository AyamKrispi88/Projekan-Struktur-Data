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



int main(){
    int pil;
    char userMasuk[100];
    do
    {
        printf("Menu Pilihan: ");
        printf("Login");
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
