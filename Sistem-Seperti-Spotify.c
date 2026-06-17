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
        printf("\n1. Login\n2. Registrasi\n3. Keluar\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &pil);
        switch (pil)
        {
        case 1:{
            login(userMasuk);
            if (login(userMasuk)){
                printf("Selamat datang @%s", userMasuk);
                menuLogined(userMasuk);
            }
            break;
        }
        case 2:{
            registrasi();
            break;
        }
        case 3:{
            printf("\nBaik, TRMKSH.\n");
            break;
        }
        default:{
            printf("\nMasukkin pilihan yang bener lah\n");
            break;
        }
        } 
    } while (pil != 3);
    
}

void menuLogined(char *usermasuk){
    int pil;  
    do
    {
        /* code */
    } while (pil != 6);
    
}
