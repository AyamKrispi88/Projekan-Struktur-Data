/*Ini buat di Login, registrasi, dan logout*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <direct.h>

void registrasi();
int cekUsn(char *username);
int login(char *username);
void hapusAkun(char *username);
void hapusIsiFolder(char *path);


typedef struct userData
{
    char username[100];
    char password[100];
}userData;


int cekUsn(char *username){
    char userUsn[100], userPw[100];
    char path[900];
    sprintf(path, "DataSentral/user.txt");
    FILE *data = fopen(path, "r");
    if (data == NULL){
        printf("\nSistem Error\n");
        return 0;
    }
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
    char path[100];
    FILE *dataUtama, *playlst;
    awalRegist:
    printf("\nRegistrasi akun\n");
    printf("Masukkan Username kamu(Tanpa Spasi dan Gabisa diubah): ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0';
    if (strchr(user.username, ' ') != NULL){
        printf("\nUsername tidak boleh ada spasi\n");
        goto awalRegist;
    }
    if (cekUsn(user.username)){ //ini artinya, if fungsi ini true
        printf("\nIni usernamenya udah ada, pake username lain\n");
        goto awalRegist;
    }

    ulangRegistPassword:
    printf("Masukkan passwordnya(Tanpa Spasi dan Gabisa diubah): ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0';
    if (strchr(user.password, ' ') != NULL){
        printf("\nUdah dibilang gaboleh ada spasi, masukkin ulang\n");
        goto ulangRegistPassword;
    }
    dataUtama = fopen("DataSentral/user.txt", "a");
    if (dataUtama == NULL){
        printf("\nError, sistemnya gabisa jalan\n");
        return;
    }

    fprintf(dataUtama, "%s %s\n", user.username, user.password);
    fclose(dataUtama);
    mkdir(user.username);
    sprintf(path, "%s/playlist.txt", user.username);
    playlst = fopen(path, "w");
    if (playlst == NULL){
        printf("\nSistem error\n");
        return;
    }
    fclose(playlst);

    printf("Selamat datang %s", user.username);
    return;
}

int login(char *userMasuk){
    userData Userlogin;
    FILE *user;
    char usn[100], userPw[100];
    int ditemukan;
    ulang:
    ditemukan = 0;
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
        return 0;
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
    FILE *data, *temp;
    char usn[100], pw[100];
    printf("\nHapus Akun\n");

    data = fopen("DataSentral/user.txt", "r");
    temp = fopen("DataSentral/temp.txt", "w");

    if (data == NULL || temp == NULL){
        printf("\nError\n");
        return;
    }

    while (fscanf(data, "%s %s", usn, pw) != EOF)
    {
        if (strcmp(usn, username) != 0){
            fprintf(temp, "%s %s\n", usn, pw);
        }
    }

    fclose(data);
    fclose(temp);

    remove("DataSentral/user.txt");
    rename("DataSentral/temp.txt", "DataSentral/user.txt");
    
    hapusIsiFolder(username);

    if (rmdir(username) == 0){
        printf("\nDone, akun berhasil dihapus\n");
    } else {
        printf("\nSistem error\n");
    }
    
}

void hapusIsiFolder(char *path){
    struct dirent *entry;
    DIR *directory = opendir(path);

    char fullPath[100];

    if (directory == NULL){
        printf("\nData user tidak ada\n");
        return;
    }

    while ((entry = readdir(directory)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }
        sprintf(fullPath, "%s/%s", path, entry->d_name);
        remove(fullPath);
    }
    closedir(directory);
}

