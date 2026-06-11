/*Ini buat di Login, registrasi, dan logout*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void registrasi();
int cekUsn(char *username);
int login(char *username);

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

    fclose(data);
    return 0;
}

void registrasi(){
    userData user;
    char pil;
    FILE *dataUtama;
    awalRegist:
    printf("\nRegistrasi akun\n");
    printf("Masukkan Username kamu(Gabisa diubah): ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0';

    if (cekUsn(user.username)){ //ini artinya, if fungsi ini true
        printf("\nIni usernamenya udah ada, pake username lain\n");
        printf("\nMau input username ulang?: ");
        if (pil == 'y' || pil == 'Y'){
            goto awalRegist;
        } else if (pil == 'n' || pil == 'N'){
            return;
        } else {
            printf("\nBenerin dikit lah inputnya\n");
        }
    }

    printf("Masukkan passwordnya(Gabisa diubah): ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0';

    dataUtama = fopen("DataSentral/user.txt", "a");
    if (dataUtama == NULL){
        printf("\nError, sistemnya gabisa jalan\n");
        return;
    }

    fprintf(dataUtama, "%s||%s\n", user.username, user.password);
    fclose(dataUtama);
    mkdir(user.username);

    printf("Selamat datang %s", user.username);

}

int login(char *username){
    userData login;
    FILE *user;
    char usn[100], userPw[100];
    printf("Masukkan Username kamu: ");
    fgets(login.username, sizeof(login.username), stdin);
    login.username[strcspn(login.username, "\n")] = '\0';
    printf("Masukkan Password: ");
    fgets(login.password, sizeof(login.password), stdin);
    login.password[strcspn(login.password, "\n")] = '\0';

    char path;
    sprintf(path, "DataSentral/user.txt");
    user = fopen(path, "r");

    while (user != EOF){

        if (user == NULL){

        }
        (fscanf(user, "%s %s", usn, userPw));
        if (strcm(username, usn) == 1){
            if (strcmp(login.password, userPw) == 1){
            }
            if (strcmp(login.password, userPw) == 0){
                printf("\nPassword atau Usernamenya salah, masukkan ulang\n");
            }
        } else {
            printf("\nPassword atau usernamenya salah, masukkan ulang\n");
        }
    }
    fclose(user);

}

void hapusAkun(char *username){

}