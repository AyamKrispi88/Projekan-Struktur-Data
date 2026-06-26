#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void buatPlaylist(char *username);
void hapusPlaylist(char *username);
void viewPlaylist(char *username);
void tambahLaguKePlaylist(char *username, char *namaPlaylist);
void hapusLagu(char *username, char *namaPlaylist);
void menuAturPlaylist(char *userMasuk);
void menuAturIsiPlaylist(char *username, char *namaPlayList);

void buatPlaylist(char *username) {
    char namaPlaylist[100];
    char path[256];
    char wei[256];
    char listPlaylist[200];
    char ww[256];
    char playlistName[200];
    sprintf(listPlaylist, "%s/listPlaylist.txt", username);
    FILE *dataPlaylist = fopen(listPlaylist, "r");
    if (dataPlaylist == NULL){
        printf("\nSistem error\n");
        return;
    }

    while (1){
        int d = 0;
        rewind(dataPlaylist);
        printf("\n--- Buat Playlist Baru ---\n");
        printf("Masukkan nama playlist baru (misal: Favorit): ");
        fgets(namaPlaylist, sizeof(namaPlaylist), stdin);
        namaPlaylist[strcspn(namaPlaylist, "\n")] = '\0'; // Hapus karakter newline
        if(strchr(namaPlaylist, ' ') != NULL){
            printf("\nPlaylist gaboleh ada spasi\n");
        } else {
            while (fgets(playlistName, sizeof(playlistName), dataPlaylist) != NULL){
                playlistName[strcspn(playlistName, "\n")] = '\0';
                if (strcmp(playlistName, namaPlaylist) == 0){
                    d = 1;
                    break;
                }
            }
        if (d == 1){
        printf("\nPlaylist dengan nama %s sudah ada, buat dengan nama lainnya\n", namaPlaylist);
        continue;
        }
        }
        break;
    }
    fclose(dataPlaylist);
    // Format path: "nama_user/nama_playlist.txt"
    sprintf(path, "%s/%s.txt", username, namaPlaylist);
    sprintf(wei, "%s/listPlaylist.txt", username);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Gagal membuat playlist. Pastikan folder user '%s' sudah ada.\n", username);
        return;
    }
    fclose(file);
    printf("Playlist '%s.txt' sukses dibuat di folder @%s!\n", namaPlaylist, username);
    FILE *plylistHimp = fopen(wei, "a");
    if (plylistHimp == NULL){
        printf("\nSistem error\n");
    }

    fprintf(plylistHimp, "%s\n", namaPlaylist);
    fclose(plylistHimp);

}

void hapusPlaylist(char *username){
    printf("\nHAPUS Playlist\n");
    FILE *playlist, *temp;
    char path[200], way[200], tempPath[200];
    char listPlaylist[200], namaPlaylist[200], tempPlaylist[200];
    sprintf(path, "%s/listPlaylist.txt", username);
    sprintf(tempPath, "%s/temp.txt", username);
    playlist = fopen(path, "r");
    if (playlist == NULL){
        printf("\\nSistem Eror\n");
        return;
    }

    int n = 0;
    int d = 1;
    printf("\nList Playlist\n");
    while (fgets(listPlaylist, sizeof(listPlaylist), playlist) != NULL)
    {
        listPlaylist[strcspn(listPlaylist, "\n")] = '\0';
        n = 1;
        printf("%d. %s\n", d, listPlaylist);
        d++;
    }
    if (n == 0)
    {
        printf("\nTidak ada playlist\n");
        fclose(playlist);
        return;
    }
    temp = fopen(tempPath, "w");
    while (1)
    {
    d = 0;
    rewind(playlist);
    printf("Masukkan nama playlist yang ingin dihapus: ");
    fgets(namaPlaylist, sizeof(namaPlaylist), stdin);
    namaPlaylist[strcspn(namaPlaylist, "\n")] = '\0';
    while (fgets(listPlaylist, sizeof(listPlaylist), playlist) != NULL)
    {
    listPlaylist[strcspn(listPlaylist, "\n")] = '\0';
    if (strcmp(listPlaylist, namaPlaylist) == 0){
        d = 1;
        while (fgets(listPlaylist, sizeof(listPlaylist), playlist) != NULL)
        {
            listPlaylist[strcspn(listPlaylist, "\n")] = '\0';
            if (strcmp(listPlaylist, namaPlaylist) != 0){
                fprintf(temp, "%s", listPlaylist);
            }
        }
        
    } else {
        printf("\nItu nama playlist yang dimasukkan salah, input ulang\n");
        continue;
    }
    }
    break;
    }
    fclose(playlist);
    fclose(temp);
    remove(path);
    rename(tempPath, path);
    sprintf(way, "%s/%s.txt", username, namaPlaylist);
    printf("\nPlaylist %s berhasil dihapus\n", namaPlaylist);
    remove(way);
}

void viewListPlaylist(char *username){
    FILE *plylst;
    char path[200];
    char namaPlaylist[200];
    char plihan[200];
    sprintf(path, "%s/listPlaylist.txt", username);
    plylst = fopen(path, "r");
    if (plylst == NULL){
        printf("Sistem Error\n");
        return;
    }
    int dataM = 0;
    int d = 1;
    printf("List playlist @%s: \n", username);
    while (fgets(namaPlaylist, sizeof(namaPlaylist), plylst) != NULL){
        dataM = 1;
        printf("%d. %s", d, namaPlaylist);
        d++;
    }

    if (dataM == 0){
        printf("\nBelum ada playlist\n");
        fclose(plylst);
        return;
    }

    char decide;
    do
    {
        printf("\nMau edit playlist? y/n: ");
        scanf(" %c", &decide);
        getchar();
        if (decide == 'Y' || decide == 'y'){
        printf("\nMasukkan nama playlist yang dipilih: ");
        fgets(plihan, sizeof(plihan), stdin);
        plihan[strcspn(plihan, "\n")] = '\0';
        rewind(plylst);
        while (fgets(namaPlaylist, sizeof(namaPlaylist), plylst))
        {
            namaPlaylist[strcspn(namaPlaylist, "\n")] = '\0';
            if (strcmp(namaPlaylist, plihan) == 0){
                menuAturIsiPlaylist(username, plihan);
                fclose(plylst);
                return;
            }
        }
    } else if(decide =='n' || decide == 'N'){
        fclose(plylst);
        return;
    } else {
        printf("\nPilihan anda tidak valid\n");
    }
    } while (1);

}

void tambahLaguKePlaylist(char *username, char *namaPlaylist) {
    char path[256];
    char buffer[256];
    char daftarLagu[100][256]; // Maksimal menampung 100 lagu dari DB
    int jumlahLagu = 0;
    int pilihan;

    // Membaca database lagu di dalam folder DataSentral
    FILE *dbMusik = fopen("DataSentral/musiks.txt", "r"); 
    if (dbMusik == NULL) {
        printf("\nError: File 'DataSentral/musiks.txt' tidak ditemukan!\n");
        printf("Pastikan kamu sudah membuat file musiks.txt di dalam folder DataSentral.\n");
        return;
    }

    // Menampilkan daftar lagu ke user
    printf("\n--- Daftar Lagu yang Tersedia ---\n");
    while (fgets(buffer, sizeof(buffer), dbMusik) != NULL && jumlahLagu < 100) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        strcpy(daftarLagu[jumlahLagu], buffer); 
        printf("%d. %s\n", jumlahLagu + 1, daftarLagu[jumlahLagu]);
        jumlahLagu++;
    }
    fclose(dbMusik);

    if (jumlahLagu == 0) {
        printf("Database lagu kosong.\n");
        return;
    }

    // Meminta input nomor lagu
    printf("\nPilih nomor lagu untuk ditambahkan ke [%s]: ", namaPlaylist);
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Harus berupa angka.\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); 

    // Validasi input nomor lagu
    if (pilihan < 1 || pilihan > jumlahLagu) {
        printf("Nomor lagu tidak ada dalam daftar.\n");
        return;
    }

    // Membuka file playlist user dengan mode "a" (append)
    sprintf(path, "%s/%s.txt", username, namaPlaylist);
    FILE *filePlaylist = fopen(path, "a");
    if (filePlaylist == NULL) {
        printf("Gagal membuka playlist '%s.txt'. Apakah playlist sudah dibuat?\n", namaPlaylist);
        return;
    }

    // Menulis lagu yang dipilih ke dalam file playlist
    fprintf(filePlaylist, "%s\n", daftarLagu[pilihan - 1]);
    fclose(filePlaylist);

    printf("Sip! Lagu '%s' berhasil masuk ke playlist %s.\n", daftarLagu[pilihan - 1], namaPlaylist);
}

void hapusLagu(char *username, char *namaPlaylist) {
    char path[256], tempPath[256];
    char buffer[256];
    char laguHapus[256];
    int ketemu = 0;

    sprintf(path, "%s/%s.txt", username, namaPlaylist);
    sprintf(tempPath, "%s/temp_playlist.txt", username);

    FILE *file = fopen(path, "r");
    FILE *temp = fopen(tempPath, "w");

    if (file == NULL || temp == NULL) {
        printf("Gagal membuka playlist. Periksa kembali nama playlist kamu.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    printf("\n--- Hapus Lagu dari Playlist %s ---\n", namaPlaylist);
    printf("Ketik nama lagu beserta artis (contoh: nina - Hindia): ");
    fgets(laguHapus, sizeof(laguHapus), stdin);
    laguHapus[strcspn(laguHapus, "\n")] = '\0';

    // Proses penyalinan data kecuali lagu yang dihapus
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (strcmp(buffer, laguHapus) != 0) {
            fprintf(temp, "%s\n", buffer);
        } else {
            ketemu = 1; 
        }
    }

    fclose(file);
    fclose(temp);

    // Mengganti file lama dengan file baru yang sudah bersih
    remove(path);
    rename(tempPath, path);

    if (ketemu) {
        printf("Lagu '%s' sukses dihapus dari playlist %s.\n", laguHapus, namaPlaylist);
    } else {
        printf("Lagu '%s' tidak ditemukan di playlist ini.\n", laguHapus);
    }
}
