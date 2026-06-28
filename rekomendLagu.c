#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct lagu {
    char judul[100];        
    struct lagu *next;
}lagu;

typedef struct graph{
    char genre[100];
    int jumlahPutaran;
    lagu *listLagu;
    struct graph *next;
}graph;

typedef struct kiuw {
    char lagu[100];
    struct kiuw *next;
    struct kiuw *prev;
} kiuw;

graph *headGraph = NULL;
graph *tailGraph = NULL;
kiuw *head = NULL;
kiuw *tail = NULL;
kiuw *current = NULL;

void bangunGraph();
void updateDariHistory(char *username);
void recomendGenreTopDua(char *username);
void rekomendTop(char *username);
void putarRekomendasiAcak(char *username, char *judulPilihan);


void bangunGraph(){
    char buffer[200], path[200];
    FILE *dataMusik;
    sprintf(path, "DataSentral/musiksGenre.txt");
    dataMusik = fopen(path, "r");

    if (dataMusik == NULL){
        printf("\nSistem Error\n");
        return;
    }
    while (fgets(buffer, sizeof(buffer), dataMusik)){
        buffer[strcspn(buffer, "\n")] = '\0';
        char *judul = strtok(buffer, "|");
        char *genre = strtok(NULL, "|");
        graph *tempGenre = headGraph;

        while (tempGenre != NULL)
        {
            if (strcmp(tempGenre->genre, genre) == 0){
                break;
            }
            tempGenre = tempGenre->next;
        }
        if (tempGenre == NULL){
            graph *bangun = (graph *) malloc(sizeof(graph));
            strcpy(bangun->genre, genre);
            bangun->jumlahPutaran = 0;
            bangun->listLagu = NULL;
            bangun->next = NULL;

            if (headGraph == NULL){
                headGraph = tailGraph = bangun;
            } else {
                tailGraph->next = bangun;
                tailGraph = bangun;
            }
            tempGenre = bangun;
        }
        lagu *baru = (lagu *) malloc(sizeof(lagu));
        strcpy(baru->judul, judul);
        baru->next = NULL;

        if (tempGenre->listLagu == NULL){
            tempGenre->listLagu = baru;
        } else {
            lagu *t = tempGenre->listLagu;
            while(t->next) {
                t = t->next;
            }
            t->next = baru;
        }
    }
    fclose(dataMusik);
}


void updateDariHistory(char *username){
    char path[200];
    sprintf(path, "%s/history.txt", username);
    FILE *file = fopen(path, "r");
    if (file == NULL){
        printf("\nError\n");
        return;
    }

    char data[200];
    while(fgets(data, sizeof(data), file) != NULL){
        data[strcspn(data, "\n")] = '\0';

        char *judul = data;

        graph *g = headGraph;

        while (g != NULL){
            lagu *list = g->listLagu;

            while (list != NULL){
                if (strcmp(list->judul, judul) == 0){
                    g->jumlahPutaran++;
                    break;
                }
                list = list->next;
            }
            g = g->next;
        }
    }

    fclose(file);
}

void putarRekomendasiAcak(char *username, char *judulPilihan) {
    kiuw *t = head;
    while (t != NULL) { kiuw *hapus = t; t = t->next; free(hapus); }
    head = tail = current = NULL;
    
    FILE *isiQueue;
    char path[200];
    char laguTxt[200];
    
    sprintf(path, "%s/musiks.txt", username); 
    isiQueue = fopen(path, "r");
    if (isiQueue == NULL){
        printf("\nGagal memuat daftar lagu (musiks.txt).\n");
        return;
    }
    
    int hitung = 0;
    while (fgets(laguTxt, sizeof(laguTxt), isiQueue) !=  NULL){
        laguTxt[strcspn(laguTxt, "\n")] = '\0';
        if(strlen(laguTxt) == 0) continue;
        
        kiuw *baru = (kiuw *) malloc(sizeof(kiuw));
        strcpy(baru->lagu, laguTxt);
        baru->next = baru->prev = NULL;

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

    // Mengacak Antrian
    if (hitung > 1) {
        srand(time(NULL));
        for (int i = hitung - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            kiuw *nodeI = head, *nodeJ = head;
            for (int k = 0; k < i; k++) nodeI = nodeI->next;
            for (int k = 0; k < j; k++) nodeJ = nodeJ->next;
            
            char tempStr[100];
            strcpy(tempStr, nodeI->lagu);
            strcpy(nodeI->lagu, nodeJ->lagu);
            strcpy(nodeJ->lagu, tempStr);
        }
    }
    
    // Pindahkan lagu pilihan user ke nomor 1
    kiuw *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->lagu, judulPilihan) == 0) {
            if (temp != head) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == tail) tail = temp->prev;
                
                temp->next = head;
                temp->prev = NULL;
                head->prev = temp;
                head = temp;
            }
            break; 
        }
        temp = temp->next;
    }
    
    // Tampilkan Informasi
    current = head;
    printf("\n>>> Memutar: %s <<<\n", current->lagu);
    printf("Lagu selanjutnya telah diacak ke dalam antrian.\n");
}


void recomendGenreTopDua(char *username){
    srand((unsigned)time(NULL));
    graph *top1 = NULL;
    graph *top2 = NULL;
    lagu *temp1, *temp2;

    graph *g = headGraph;
    int jumlah;
    int jumlahRek=0;

    while (g != NULL){
        if (top1 == NULL || g->jumlahPutaran > top1->jumlahPutaran){
            top2 = top1;
            top1 = g;   
        } else if (top2 == NULL || g->jumlahPutaran > top2->jumlahPutaran){
            top2 = g;
        }
        g = g->next;
    }

    if (top1 == NULL || top1->jumlahPutaran == 0){
        return;
    } 
    
    printf("\nREKOMENDASI\n");
        if (top1 != NULL && top1->listLagu != NULL){
            temp1 = top1->listLagu;
            jumlah = 0;
            while (temp1 != NULL){
                jumlah++;
                temp1 = temp1->next;
            }

            int acak1 = rand() % jumlah;
            temp1 = top1->listLagu;
            while (acak1--){
                temp1 = temp1->next;
            }
            printf("1. %s\n", temp1->judul);
            jumlahRek++;
        } 
        if (top2 != NULL && top2->listLagu != NULL){
            jumlah = 0;
            temp2 = top2->listLagu;
            while (temp2 != NULL){
                jumlah++;
                temp2 = temp2->next;
            }

            int acak2 = rand() % jumlah;
            temp2 = top2->listLagu  ;

            while (acak2--){
                temp2 = temp2->next;
            }
            printf("2. %s\n", temp2->judul);
            jumlahRek++;
        }
        printf("3. Kembali\n");
    int pilihan;
    printf("Pilih lagu yang ingin diputar (1/2/3): ");
    
    // Validasi input angka
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid\n");
        while(getchar() != '\n'); // Bersihkan sisa karakter aneh
        return;
    }
    while(getchar() != '\n'); // Membersihkan enter (buffer)

    if (pilihan == 1 && jumlahRek >= 1 && temp1 != NULL) {
        putarRekomendasiAcak(username, temp1->judul);
    } else if (pilihan == 2 && jumlahRek == 2 && temp2 != NULL) {
        putarRekomendasiAcak(username, temp2->judul);
    } else {
        return; // User pilih 3 atau input angka yang salah
    }
}

void rekomendTop(char *username){
    bangunGraph();
    updateDariHistory(username);
    recomendGenreTopDua(username);
}