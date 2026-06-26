/*bikin antrian play musik*/
/*
Add To Queue
Play Next
View Queue
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PlaylistQueue(char *userMasuk);
void cekIsiPlaylist(char *userMasuk, char *playlistPilihan);
void buatQueue(char *userMasuk, char *playlistPilihan);
void viewQueue(char *userMasuk);
void playNext(char *userMasuk);


typedef struct kiuw
{
    char lagu[100];
    struct kiuw *next;
    struct kiuw *prev;
}kiuw;

struct kiuw *head = NULL;
struct kiuw *tail = NULL;
struct kiuw *current = NULL;


void PlaylistQueue(char *userMasuk){
    char path[200];
    sprintf(path, "%s/listPlaylist.txt", userMasuk);
    FILE *musik = fopen(path, "r"); //ini isinya nama nama file playlist di playlist.txt
    char judulPlaylist[100];
    if (musik == NULL){
        printf("\nSistem error\n");
        return;
    }

    int uruT = 1;
    char playlistPilihan[100];
    printf("\nPlaylist yang kamu punya: ");
    while (fgets(judulPlaylist, sizeof(judulPlaylist), musik) != NULL){
        judulPlaylist[strcspn(judulPlaylist, "\n")] = '\0';
        printf("\n%d. %s", uruT, judulPlaylist);
        uruT++;
    }
    fclose(musik);
    printf("Mau play Playlist yang mana? Ketik nama Playlistnya: ");
    fgets(playlistPilihan, sizeof(playlistPilihan), stdin); //stdin tu artinya standar input, atau inputan dari user
    playlistPilihan[strcspn(playlistPilihan, "\n")] = '\0';
    cekIsiPlaylist(userMasuk, playlistPilihan);
}

void cekIsiPlaylist(char *userMasuk, char *playlistPilihan){
    FILE *cekIsi;
    char path[200];
    char lagu[200];
    sprintf(path, "%s/%s.txt", userMasuk, playlistPilihan);
    cekIsi = fopen(path, "r");
    if (cekIsi == NULL){
        printf("\nAduh, sistemnya error\n");
        return;
    }

    if (fgets(lagu, sizeof(lagu), cekIsi) == NULL){
        printf("\nPlaylist belum ada isinya\n");
        fclose(cekIsi);
        return;
    }

    buatQueue(userMasuk, playlistPilihan);
}

void buatQueue(char *userMasuk, char *playlistPilihan){
    head = NULL;
    tail = NULL;
    current = NULL;
    printf("queue %s sekarang adalah: \n", userMasuk);
    FILE *isiQueue;
    char path[200];
    char lagu[200];
    sprintf(path, "%s/%s.txt", userMasuk, playlistPilihan);
    isiQueue = fopen(path, "r");
    if (isiQueue == NULL){
        printf("\nSistem Error\n");
        return;
    }
    while (fgets(lagu, sizeof(lagu), isiQueue) !=  NULL){
        lagu[strcspn(lagu, "\n")] = '\0';

        kiuw *baru = (kiuw *) malloc(sizeof(kiuw));

        strcpy(baru->lagu, lagu);
        baru->next = NULL;
        baru->prev = NULL;

        if (head == NULL){
            head = tail = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
    }
    fclose(isiQueue);
    current = head;
    viewQueue(userMasuk);
}

void viewQueue(char *userMasuk){
    kiuw *temp = head;
    int no = 1;
    if (head == NULL){
        printf("\nBelum ada lagu yang diplay\n");
        return; 
    } 

    printf("\nQueue %s\n", userMasuk);
    while (temp != NULL){
        if (temp == current){
             printf("%d. %s <-- Lagu yang lagi diplay\n", no, temp->lagu);
        } else {
            printf("%d. %s\n", no, temp->lagu);
        }
        temp = temp->next;
        no++;
    }
    
    while(1){
    printf("\nPilih: S atau s untuk skip, p atau P untuk prev, q atau Q untuk quit\n");
    char sekips;
    printf("Masukkan pilhan: ");
    scanf(" %c", &sekips);
    getchar();
    if (sekips == 's' || sekips == 'S'){
        if (current->next == NULL){
            printf("\nUdah nggak ada lagu selanjurtnya\n");
            break;
        } else {
            current = current->next;
            break;
        }
    } else if (sekips == 'p' || sekips == 'P'){
        if (current->prev == NULL){
            printf("\nTidak ada lagu sebelumnya\n");
            break;
        } else {
            current = current->prev;
            break;
        }
    } else if (sekips == 'q' || sekips == 'Q'){
        return;
    }else {
        printf("\nTolong lah, pilih yg bener\n");
    }
}
}

void clearQueue(){
    kiuw *temp = head;
    if (head == NULL){
        printf("\nQueuenya kosong\n");
        return;
    }

    kiuw *hapus;
    while (temp != NULL){
        hapus = temp;
        temp = temp->next;
        free(hapus);
    }

    head = NULL;
    tail = NULL;
    current= NULL;

    printf("\nQueue sudah dikosongkan\n");
}

void pilihanUser(char *userMasuk){
    int pil;
    do
    {
        printf("\nMenu playlist dan play stuff\n");
        printf("Pilih berdasarkan nomor urut\n1. Pilih playlist\n2. Liat Queue\n3. Clear Queue\n");
        if (scanf("%d", &pil) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        switch (pil)
        {
        case 1:{
            PlaylistQueue(userMasuk);
            break;}
        
        case 2:{
            viewQueue(userMasuk);
            break;}

        case 3:{
            clearQueue();
            break;}

        case 4:{
            printf("\nTerima kash\n");
            break;}
        
        default:{
            printf("\nPilih yang bener lah\n");
            break;}
        }
    } while (pil != 4);
    return;
    
}
