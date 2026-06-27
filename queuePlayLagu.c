/*bikin antrian play musik*/
/*
Add To Queue
Play Next
View Queue
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void PlaylistQueue(char *userMasuk);
int cekIsiPlaylist(char *userMasuk, char *playlistPilihan);
void buatStraightQueue(char *userMasuk, char *playlistPilihan);
void buatRandomtQueue(char *userMasuk, char *playlistPilihan);
void viewQueue(char *userMasuk);
void playNext(char *userMasuk);
int pilihanPlay(char *userMasuk, char *playlistPilihan);


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
        printf("\n%d. %s\n", uruT, judulPlaylist);
        uruT++;
    }
    fclose(musik);
    printf("Mau play Playlist yang mana? Ketik nama Playlistnya: ");
    fgets(playlistPilihan, sizeof(playlistPilihan), stdin); //stdin tu artinya standar input, atau inputan dari user
    playlistPilihan[strcspn(playlistPilihan, "\n")] = '\0';
    
    if (cekIsiPlaylist(userMasuk, playlistPilihan) == 0){
        return;
    }
    pilihanPlay(userMasuk, playlistPilihan);
    return;
}

int cekIsiPlaylist(char *userMasuk, char *playlistPilihan){
    FILE *cekIsi;
    char path[200];
    char lagu[200];
    sprintf(path, "%s/%s.txt", userMasuk, playlistPilihan);
    cekIsi = fopen(path, "r");
    if (cekIsi == NULL){
        printf("\nAduh, sistemnya error\n");
        return 0;
    }

    if (fgets(lagu, sizeof(lagu), cekIsi) == NULL){
        printf("\nPlaylist belum ada isinya\n");
        fclose(cekIsi);
        return 0;
    }

    return 1;
}

void buatStraightQueue(char *userMasuk, char *playlistPilihan){
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
    int hitung = 0;
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
        hitung++;
    }
    fclose(isiQueue);    
    current = head;
    viewQueue(userMasuk);
}

void viewQueue(char *userMasuk){
    kiuw *temp = head;
    int no;
    char path[100];
    if (head == NULL){
        printf("\nBelum ada lagu yang diplay\n");
        return; 
    } 
    
    perulangan:
    no = 1;
    temp = head;
    FILE *history;
    sprintf(path, "%s/history.txt", userMasuk);
    history = fopen(path, "a");
    printf("\nQueue %s\n", userMasuk);
    while (temp != NULL){
        if (temp == current){
             printf("%d. %s <-- Lagu yang lagi diplay\n", no, temp->lagu);
             fprintf(history, "%s\n", current->lagu);
             fclose(history);
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
            printf("\nUdah nggak ada lagu selanjutnya\n");
            break;
        } else {
            current = current->next;
            goto perulangan;
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

int pilihanPlay(char *userMasuk, char *playlistPilihan){
int pilihanmu;
do
{
    printf("pilih metode putar mu : \n1.Putar musik random\n2.Putar sesuai urutan playlist\n3. Kembali\n");
    printf("Masukkan pilihan berdasarkan nomor pilihan: ");
     if (scanf("%d", &pilihanmu) != 1) {
        printf("Tidak valid\n");
        while (getchar() != '\n');
        continue;
        }
        getchar();
    switch (pilihanmu)
    {
    case 1:{
        buatRandomtQueue(userMasuk, playlistPilihan);
        break;}
    case 2:{
        buatStraightQueue(userMasuk, playlistPilihan);
        break;
    }
    case 3:{
        break;
    }
    default:
        break;
    }
} while (pilihanmu != 3);
}

void buatRandomtQueue(char *userMasuk, char *playlistPilihan){

}