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

graph *headGraph = NULL;
graph *tailGraph = NULL;

void bangunGraph();
void updateDariHistory(char *username);
void recomendGenreTopDua();
void rekomendTop(char *username);

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

void recomendGenreTopDua(){
    srand((unsigned)time(NULL));
    graph *top1 = NULL;
    graph *top2 = NULL;
    lagu *temp1, *temp2;

    graph *g = headGraph;
    int jumlah;

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
        }
}

void rekomendTop(char *username){
    bangunGraph();
    updateDariHistory(username);
    recomendGenreTopDua();
}