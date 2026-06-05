/*Ini buat di Login, registrasi, dan logout*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct userData
{
    char username[1000];
    char password[100];
}userData;

int cekUsn(char *username){
    char userUsn[100], userPw[100];
    char path[900];
    sprintf(path, "DataSentral/user.txt");
    FILE *data = fopen(path, "r");

    while (fscanf(data, "%s %s", userUsn, userPw) != EOF){
        if (strcmp(username, userUsn) == 0){
            fclose(data);
            return 1;
        }
    }
}

void registrasi(){
    userData user;
    printf("\nRegistrasi akun\n");
    printf("Masukkan Username kamu: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0';
    printf("Masukkan passwordnya: ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0';

    if (cekUsn(user.username)){
        printf("\nIni usernamenya udah ada, pake username lain\n");
    }
}

void login(){
    userData login;
    FILE *user;
    printf("Masukkan Username kamu: ");
    fgets(login.username, sizeof(login.username), stdin);
    strcspn
    printf("Masukkan Password: ");
    fgets(login.password, sizeof(login.password), stdin);
    strcspn
}