/*Ini buat di Login, registrasi, dan logout*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct userData
{
    char username[1000];
    char password[100];
}userData;

void cekUsn(){

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