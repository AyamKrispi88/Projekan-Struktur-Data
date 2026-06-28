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
#include "rekomendasi.c"
#include "playedHistory.c"


void menuLogined(char *usermasuk);
void pilihanUser(char *userMasuk);
void menuAturPlaylist(char *userMasuk);
void menuAturIsiPlaylist(char *username, char *namaPlayList);
void pilihanGenre();

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
        rekomendTop(usermasuk);
        printf("\nMenu\n1. Hapus Akun\n2. Liat seluruh lagu berdasarkan genre\n3. Playlist stuff\n4. Play musik\n5. Play salah satu lagu rekomendasi\n6. Keluar\n");
        printf("Masukkan pilihan: ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
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
            pilihanUser(usermasuk);
            break;
        }
        case 5:{
            pilihan(usermasuk);
            break;
        }
        case 6:{
            printf("\nTerima kasih\n");
            break;
        }
        default:{
            printf("\nPilih yang bener lah\n");
            break;}
        }
    } while (pil != 6);
    
}  

void pilihanUser(char *userMasuk){
    int pil;
    do
    {
        printf("\nMenu playlist dan play stuff\n");
        printf("Pilih berdasarkan nomor urut\n1. Play lagu dan queue random\n2. Pilih playlist untuk diplay\n3. Liat Queue\n4. Clear Queue\n5. History\n6. Keluar\n\n");
        printf("Masukkan pilihan: ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
        switch (pil)
        {
        case 1:{
            jalankanAplikasi(userMasuk);
            break;
        }
        case 2:{
            PlaylistQueue(userMasuk);
            break;}
        
        case 3:{
            viewQueue(userMasuk);
            break;}

        case 4:{
            clearQueue();
            break;}
        
        case 5:{
            lihatHistory(userMasuk);
            break;
        }
        case 6:{
            printf("\nTerima kasih\n");
            break;}
        
        default:{
            printf("\nPilih yang bener lah\n");
            break;}
        }
    } while (pil != 6);
    return;
    
}

void menuAturPlaylist(char *userMasuk){
    int pil;
    do
    {
        printf("\nMenu:\n");
        printf("1. Buat Playlist\n2. Playlist\n3. Hapus Playlist\n4. Keluar\n");
        printf("Masukkan pilihan: ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
        switch (pil)
        {
        case 1:{
            buatPlaylist(userMasuk);
            break;}
        
        case 2:{
            viewListPlaylist(userMasuk);
            break;
        }
        case 3:{
            hapusPlaylist(userMasuk);
            break;
        }
        case 4:{
            printf("\nTerima kasih\n");
            return;
        }
        default:{
            break;}
        }
    } while (pil != 4);
    
}

void menuAturIsiPlaylist(char *username, char *namaPlayList){
    int pil;
    do
    {
        printf("\nMenu:\n1. Tambah lagu ke playlist\n2. Hapus lagu dari playlist\n3. Liat isi playlist\n4. Keluar\n");
        printf("\nMasukkan pilihan:");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
        switch (pil)
        {
        case 1:{
            tambahLaguKePlaylist(username, namaPlayList);
            break;}
        case 2:{
            hapusLagu(username, namaPlayList);
            break;
        }
        case 3:{
            liatIsiPlaylist(username, namaPlayList);
            break;
        }
        case 4:{
            printf("\nTerima Kasih\n");
            return;
        }
        default:{
            break;}
        }
    } while (pil != 4);
}

void pilihanGenre(){
    int pil;
    bacaMusik();

    do
    {
        printf("\nMenu:\n1. Semua musik berdasarkan genre\n2. Rock\n3. Pop\n4. Indie\n5. Jazz\n6. Reggae(Regge)\n7. Keluar\n");
        printf("Masukkan pilihan(berdasarkan nomor): ");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
        switch (pil)
        {
        case 1:{
            printf("Daftar seluruh lagu berdasarkan genre: ");
            inorder(root);
            break;}
        
        case 2:{
            showMusik(cariGenre(root, "Rock"));
            break;}

        case 3:{
            showMusik(cariGenre(root, "Pop"));
            break;}

        case 4:{
            showMusik(cariGenre(root, "Indie"));
            break;}
        case 5:{
            showMusik(cariGenre(root, "Jazz"));
        }
        case 6:{
            showMusik(cariGenre(root, "Reggae"));
            break;
        }
        
        case 7:{
            printf("\nTerimksh\n");
            break;}
        
        default:{
            break;
        }
        }
    } while (pil != 7);
    
}
