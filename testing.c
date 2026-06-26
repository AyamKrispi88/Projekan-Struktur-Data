#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "user.c"
#include "playlist.c"
#include "queuePlayLagu.c"
#include "genrePengelompokkanLagu.c"
#include "rekomendLagu.c"


void menuLogined(char *usermasuk);

int main(){
    int pil;
    char userMasuk[100];
    do
    {
        printf("Menu Pilihan: ");
        printf("\n1. Login\n2. Registrasi\n3. Keluar\n");
        printf("Masukkan Pilihan: ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
        switch (pil)
        {
        case 1:{
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
    return 0;
}


void menuLogined(char *usermasuk){
    int pil;  
    do
    {
        printf("\nMenu\n1. Hapus Akun\n2. Liat seluruh lagu berdasarkan genre\n3. Playlist stuff\n");
        printf("Masukkan pilihan: ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        switch (pil)
        {
        case 1:{
            hapusAkun(usermasuk);
            return;
            break;}
        case 2:{
            pilihanGenre();
            break;
        }
        case 3:{
            menuAturPlaylist(usermasuk);
            break;
        }
        case 4:{
            printf("\nTerima kasih\n");
            break;
        }
        default:{
            printf("\nPilih yang bener lah\n");
            break;}
        }
    } while (pil != 4);
    
}
