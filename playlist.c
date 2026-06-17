#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max = 10;
int banyak = 0;

typedef struct playlist {
    char judul[100];
    struct playlist *next;
} playlist;

typedef struct folder {
    char nama[100];
    playlist *head;
} folder;
folder list[10]; 

void buat() {
    if (banyak >= max) {
        printf("Jumlah playlist sudah penuh!\n");
        return;
    }

    printf("Masukkan nama playlist anda: ");
    while(getchar() != '\n'); 
    
    fgets(list[banyak].nama, sizeof(list[banyak].nama), stdin);
    list[banyak].nama[strcspn(list[banyak].nama, "\n")] = 0;
    
    list[banyak].head = NULL;
    
    banyak++;
    printf("Playlist '%s' berhasil dibuat!\n", list[banyak-1].nama);
}

void tambah() {
    if (banyak == 0) {
        printf("Belum ada playlist! Silakan buat playlist terlebih dahulu.\n");
        return;
    }

    printf("Pilih Playlist\n");
    for (int i = 0; i < banyak; i++) {
        printf("[%d] %s\n", i, list[i].nama);
    }

    int idx;
    printf("Masukkan nomor folder: ");
    scanf("%d", &idx);

    if (idx < 0 || idx >= banyak) {
        printf("Indeks tidak valid!\n");
        return;
    }

    playlist *newSong = (playlist*)malloc(sizeof(playlist));
    printf("Masukkan judul lagu: ");
    while(getchar() != '\n'); 
    fgets(newSong->judul, sizeof(newSong->judul), stdin);
    newSong->judul[strcspn(newSong->judul, "\n")] = 0;
    newSong->next = NULL;

    if (list[idx].head == NULL) {
        list[idx].head = newSong;
    } else {
        playlist *temp = list[idx].head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Lagu '%s' ditambahkan ke '%s'.\n", newSong->judul, list[idx].nama);
}
