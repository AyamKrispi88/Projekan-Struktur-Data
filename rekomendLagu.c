#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 1. Struct untuk LinkedList lagu (node playlist)
typedef struct playlist {
    char judul[100];        
    struct playlist *next;  
} playlist;

// 2. Struct untuk Folder yang menyimpan playlist
typedef struct {
    char nama[100];         
    playlist *head;         
} Folder;

// 3. Variabel Global
Folder folderList[10];     
int banyak = 0;             

// ========================================================

void playLagu() {
    if (banyak == 0) {
        printf("\nBelum ada playlist untuk diputar.\n");
        return;
    }

    // 1. Pilih Folder
    printf("\n=== PILIH FOLDER UNTUK DIPUTAR ===\n");
    for (int i = 0; i < banyak; i++) {
        printf("[%d] Folder: %s\n", i, folderList[i].nama);
    }
    
    int idx;
    printf("Pilih nomor folder: ");
    scanf("%d", &idx);

    if (idx < 0 || idx >= banyak || folderList[idx].head == NULL) {
        printf("Folder tidak valid atau masih kosong!\n");
        return;
    }

    // 2. Hitung total lagu di dalam folder ini
    int jumlahLagu = 0;
    playlist *temp = folderList[idx].head;
    while (temp != NULL) {
        jumlahLagu++;
        temp = temp->next;
    }

    // 3. Tampilkan lagu agar user bisa memilih lagu pertama
    printf("\n--- Isi Playlist '%s' ---\n", folderList[idx].nama);
    temp = folderList[idx].head;
    int nomor = 1;
    while (temp != NULL) {
        printf("%d. %s\n", nomor++, temp->judul);
        temp = temp->next;
    }

    int pilihanLagu;
    printf("Pilih nomor lagu yang ingin diputar pertama (1-%d): ", jumlahLagu);
    scanf("%d", &pilihanLagu);

    // Menuju ke lagu pilihan user
    temp = folderList[idx].head;
    for (int i = 1; i < pilihanLagu && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Lagu tidak ditemukan!\n");
        return;
    }

    // Putar lagu utama
    printf("SEDANG MEMUTAR: %s\n", temp->judul);

    // Bersihkan buffer enter dari scanf sebelumnya
    while(getchar() != '\n'); 

    // 4. Sistem Autoplay Berputar (Random)
    char aksi;
    while (1) {
        printf("\n[Tekan ENTER untuk lagu rekomendasi selanjutnya , Ketik 'q' lalu ENTER untuk stop : ");
        aksi = getchar();
        
        if (aksi == 'q' || aksi == 'Q') {
            printf("Pemutaran dihentikan.\n");
            break; 
        }

        // Jika lagu cuma 1, putar itu terus
        if (jumlahLagu == 1) {
            printf(" SEDANG MEMUTAR: %s\n", folderList[idx].head->judul);
            continue;
        }

        // Generate angka acak (0 sampai jumlahLagu - 1)
        int randomAcak = rand() % jumlahLagu;
        
        // Mulai lagi dari head, lalu maju sebanyak angka acak
        playlist *laguRekomendasi = folderList[idx].head;
        for (int i = 0; i < randomAcak; i++) {
            laguRekomendasi = laguRekomendasi->next;
        }
        printf("SEDANG MEMUTAR: %s\n", laguRekomendasi->judul);
    }
}


/*
Rekomendasi lagu
Show Recommendation
make graph
*/

