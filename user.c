/*Ini buat di Login, registrasi, dan logout*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <direct.h>

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
        ulangPlih:
        printf("\nMau input username ulang?: ");
        scanf(" %c", &pil);
        while (getchar() != '\n');
        if (pil == 'y' || pil == 'Y'){
            goto awalRegist;
        } else if (pil == 'n' || pil == 'N'){
            return;
        } else {
            printf("\nBenerin dikit lah inputnya\n");
            goto ulangPlih;
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

    fprintf(dataUtama, "%s %s\n", user.username, user.password);
    fclose(dataUtama);
    mkdir(user.username);

    printf("Selamat datang %s", user.username);
    return;
}

int login(char *userMasuk){
    userData Userlogin;
    FILE *user;
    char usn[100], userPw[100];
    ulang:
    int ditemukan = 0;
    printf("Masukkan Username kamu: ");
    fgets(Userlogin.username, sizeof(Userlogin.username), stdin);
    Userlogin.username[strcspn(Userlogin.username, "\n")] = '\0';
    printf("Masukkan Password: ");
    fgets(Userlogin.password, sizeof(Userlogin.password), stdin);
    Userlogin.password[strcspn(Userlogin.password, "\n")] = '\0';

    char path[100];
    sprintf(path, "DataSentral/user.txt");
    user = fopen(path, "r");
    if (user == NULL){
        printf("Aduh sistem error");
        }

    while (fscanf(user, "%s %s", usn, userPw)!= EOF ){
        if (strcmp(Userlogin.username, usn) == 0){
            ditemukan = 1;
            if (strcmp(Userlogin.password, userPw) == 0){
                printf("\nSudah berhasil login, selamat datang @%s\n", Userlogin.username);
                strcpy(userMasuk, Userlogin.username);
                fclose(user);
                return 1;
            } else {
                printf("\nPassword atau Usernamenya salah, masukkan ulang\n");
                fclose(user);
                goto ulang;
            }
        }
    }
    fclose(user);
    if (!ditemukan){
        printf("\nUsernamenya ga ada\n");
        goto ulang;
    }
    return 0;
}

void hapusAkun(char *username){
    
}