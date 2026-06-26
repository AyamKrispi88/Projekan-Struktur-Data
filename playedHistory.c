#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void lihatHistory(char *username) {
    char path[256];
    char buffer[256];
    int nomor = 1;
    
    // Menyesuaikan path ke folder masing-masing user (seperti di user.c & playlist.c)
    sprintf(path, "%s/history.txt", username);
    
    // Membuka file history dengan mode "r"
    FILE *fileHistory = fopen(path, "r");
    if (fileHistory == NULL) {
        printf("\nBelum ada riwayat musik yang diputar untuk %s.\n", username);
        return;
    }
    
    printf("\n=== RIWAYAT MUSIK %s ===\n", username);
    
    // Membaca file baris demi baris sampai data habis
    while (fgets(buffer, sizeof(buffer), fileHistory) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printf("[%d] %s\n", nomor, buffer);
        nomor++;
    }
    
    fclose(fileHistory);
}



/*
hystory played song intinya
Push History
Previous Song
View History
*/