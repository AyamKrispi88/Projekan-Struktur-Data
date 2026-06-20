/*bikin antrian play musik*/
/*
Add To Queue
Play Next
View Queue
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct kiuw
{
    char lagu[100];
    char penyanyi[100];
    struct kiuw *next;
    struct kiuw *prev;
}kiuw;

struct kiuw *head = NULL;

void AddToQueue(){
    kiuw *node = (kiuw *) malloc(sizeof(kiuw));
    FILE *musik = fopen("DataSentral/user.txt", "r");
    if (musik == NULL){
        printf("\nSistem error\n");
    }
    printf("\nList lagu\n");
    while (musik != EOF){
        printf("%s %s", node->lagu, node->penyanyi);
    }
    printf("\nMau nambah lagu yang mana?: \n");
    printf("\nPilih berdasarkan no urut\n");


}

void playNext(){
    printf("\nKetik S atau s untuk skip||Ketik P atau p untuk ke lagu sebelumnya\n");
    char pilihan;
    printf("Pilihan: ");
}

void viewQueue(){

}

int main(){

}
