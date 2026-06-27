#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct playlist {
    char judul[100];        
    struct playlist *next;
} playlist;

// Fungsi untuk membaca semua lagu dari file musiks.txt ke dalam Linked List
playlist* loadLaguDariFile(int *totalLagu) {
    FILE *file = fopen("DataSentral/musiks.txt", "r");
    
    if (file == NULL) {
        printf("[Peringatan] File 'DataSentral/musiks.txt' tidak ditemukan!\n");
        return NULL;
    }

    playlist *head = NULL;
    playlist *tail = NULL;
    *totalLagu = 0; 

    char judulLagu[100];

    while (fgets(judulLagu, sizeof(judulLagu), file)) {
        judulLagu[strcspn(judulLagu, "\r\n")] = 0;

        if (strlen(judulLagu) == 0) continue;

        playlist *nodeBaru = (playlist*) malloc(sizeof(playlist));
        strcpy(nodeBaru->judul, judulLagu);
        nodeBaru->next = NULL;

        if (head == NULL) {
            head = nodeBaru;
            tail = nodeBaru;
        } else {
            tail->next = nodeBaru;
            tail = nodeBaru;
        }
        
        (*totalLagu)++; 
    }

    fclose(file); 
    return head; 
}

// Fungsi utama untuk memutar lagu dan melakukan autoplay random
void putarDanAutoplay(char *username, playlist *head, int totalLagu) {
    FILE *file;
    char path[200];
    printf("\n%s\n", username);
    sprintf(path, "%s/history.txt", username);
    file = fopen(path, "a");
    if (file == NULL){
        printf("\nSistem error\n");
        return;
    }
    if (head == NULL || totalLagu == 0) {
        printf("Tidak ada lagu yang bisa diputar.\n");
        return;
    }

    srand(time(NULL)); 

    playlist *temp = head;
    int nomor = 1;
    while (temp != NULL) {
        printf("%d. %s\n", nomor++, temp->judul);
        temp = temp->next;
    }

    int pilihanLagu;
    printf("\nPilih nomor lagu untuk diputar pertama (1-%d): ", totalLagu);
    scanf("%d", &pilihanLagu);

    if (pilihanLagu < 1 || pilihanLagu > totalLagu) {
        printf("Pilihan tidak valid! Program keluar.\n");
        return;
    }

    temp = head;
    for (int i = 1; i < pilihanLagu && temp != NULL; i++) {
        temp = temp->next;
    }

    printf("SEDANG MEMUTAR: %s\n", temp->judul);
    fprintf(file, "%s\n", temp->judul);
    

    while(getchar() != '\n'); 

    char aksi;
    while (1) {
        printf("\nTekan ENTER untuk lagu random berikutnya Atau Ketik 'q' lalu ENTER untuk stop : ");
        aksi = getchar();
        
        if (aksi == 'q' || aksi == 'Q') {
            printf("Pemutaran musik dihentikan. Sampai jumpa!\n");
            break; 
        }

        if (totalLagu == 1) {
            printf("\n>>> SEDANG MEMUTAR: %s <<<\n", head->judul);
            continue;
        }

        int indeksAcak = rand() % totalLagu;
        
        playlist *laguAcak = head;
        for (int i = 0; i < indeksAcak; i++) {
            laguAcak = laguAcak->next;
        }
        
        printf(" SEDANG MEMUTAR (RANDOM): %s \n", laguAcak->judul);
        fprintf(file, "%s\n", laguAcak->judul);
        
    }
    fclose(file);
}

void jalankanAplikasi(char *usermasuk) {
    int jumlahLagu = 0;
    printf("\nHai @%s\n", usermasuk);
    
    // Ambil data dari file musiks.txt dan simpan ke Linked List
    playlist *daftarLagu = loadLaguDariFile(&jumlahLagu);

    // Jalankan sistem pemutar musik jika data lagu ada
    if (daftarLagu != NULL) {
        putarDanAutoplay(usermasuk, daftarLagu, jumlahLagu);
    }
}