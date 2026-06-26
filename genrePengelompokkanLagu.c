/*
Ngelola genre lagu
Display Genre
Show Songs By Genre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct songs
{
    char judul[100];
    struct songs *next;
}songs;

typedef struct nodeGenre
{
    char genre[20];
    songs *headLagu;
    
    struct nodeGenre *kiri;
    struct nodeGenre *kanan;    
}nodeGenre;

nodeGenre *root = NULL;


nodeGenre *buatGenre(char genre[]){
    nodeGenre *baru = (nodeGenre *) malloc(sizeof(nodeGenre));

    strcpy(baru->genre, genre);
    baru->headLagu = NULL;
    baru->kanan = NULL;
    baru->kiri = NULL;

    return baru;
}

nodeGenre *insertGenre(nodeGenre *root, char genre[]){
    if (root == NULL){
        return buatGenre(genre);
    }

    if (strcmp(genre, root->genre) < 0){
        root->kiri = insertGenre(root->kiri, genre);
    } else if (strcmp(genre, root->genre) > 0){
        root->kanan = insertGenre(root->kanan, genre);
    }

    return root;
}

nodeGenre *cariGenre(nodeGenre *root, char genre[]){
    if (root ==  NULL){
        return NULL;
    }

    if (strcmp(genre, root->genre) == 0){
        return root;
    }

    if (strcmp(genre, root->genre) < 0){
        return cariGenre(root->kiri, genre);
    }

    return cariGenre(root->kanan, genre);
}

void tambahLaguGenre(nodeGenre *genreNode, char judul[]){
    songs *baru = (songs *) malloc(sizeof(songs));
    strcpy(baru->judul, judul);
    baru->next = NULL;

    if (genreNode->headLagu == NULL){
        genreNode->headLagu = baru;
    } else {
        songs *temp = genreNode->headLagu;

        while (temp->next != NULL){
            temp = temp->next;
        }

        temp->next = baru;
    }
}

void bacaMusik(){
    FILE *Musiks = fopen("DataSentral/musiksGenre.txt", "r");

    if (Musiks == NULL){
        printf("\nSistem error\n");
        return;
    }

    char baris[300];
    char judul[100];
    char genre[40];

    while(fgets(baris, sizeof(baris), Musiks) != NULL ){
        baris[strcspn(baris, "\n")] = '\0';
        sscanf(baris, "%[^|]|%[^\n]", judul, genre);

        nodeGenre *genreNode = cariGenre(root, genre);

        if (genreNode == NULL){
            root = insertGenre(root, genre);
            genreNode = cariGenre(root, genre);
        }
        tambahLaguGenre(genreNode, judul);
    }

    fclose(Musiks);
}

void showMusik(nodeGenre *genreNode){
    if (genreNode == NULL){
        return;
    }

    printf("\nGenre: %s\n", genreNode->genre);
    songs *temp = genreNode->headLagu;

    int i = 1;

    while (temp != NULL){
        printf("%d. %s\n", i, temp->judul);
        temp = temp->next;
        i++;
    }
}

void inorder(nodeGenre *root){
    if (root == NULL){
        return;
    }

    inorder(root->kiri);
    showMusik(root);
    inorder(root->kanan);
}

