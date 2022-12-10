#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void login();
int checkPassword(char *PasswordInserted, int IndexUsername);
void inputPassword(int IndexUsername),
    changePassword(int Indexakun);

int main(int argc, char const *argv[])
{
    login();
    changePassword(2);
    return 0;
}

void login()//menu login
{
    system("cls");
    char username[20];
    int i;

    while (1)
    {
        printf("USERNAME : ");
        gets(username);
        while (username[i])
        {
            username[i] = tolower(username[i]);
            i++;
        }

        if (!strcmp(username, "admin"))
        {
            inputPassword(1);//input password, penjelasan parameter ada di fungsinya
            printf("lolos");// disini ganti pake subprogram admin
            exit(0);
        }
        else if (!strcmp(username, "gudang"))
        {
            inputPassword(2);
            printf("lolos");// sub program gudang
            exit(0);
        }
        else if (!strcmp(username, "manager"))
        {
            inputPassword(3);
            printf("lolos");// sub program manager
            exit(0);
        }
        system("cls");
        printf("\t\tusername tidak ditemukan !\n");
    }
}

void inputPassword(int IndexUsername)
// 1 = admin
// 2 = gudang
// 3 = manager
{
    char Password[20];
    while (1)
    {
        printf("PASSWORD : ");
        gets(Password);
        if (!strcmp(Password, "0"))
        {
            login();
        }

        if (checkPassword(Password, IndexUsername))
        {
            break;
        }
        else
        {
            printf("\t\tPassword salah !\n");
        }
    }
}
int checkPassword(char *PasswordInserted, int IndexUsername)
{
    int i = 1, read;
    char Password[20];
    FILE *fAkun;
    fAkun = fopen("akunPass.txt", "r");
    if (fAkun == NULL)// buat file password defult
    {
        fclose(fAkun);
        fAkun = fopen("akunPass.txt", "w");
        fprintf(fAkun,"admin\ngudang\nmanager\n");
        fclose(fAkun);
        fAkun = fopen("akunPass.txt", "r");
    }
    do
    {
        fscanf(fAkun, "%[^\n]\n", &Password);
        if (i == IndexUsername)
        {
            if (!strcmp(Password, PasswordInserted))
            {
                fclose(fAkun);
                return 1;
            }
            else
            {
                fclose(fAkun);
                return 0;
            }
        }
        i++;
    } while (!feof(fAkun));

    fclose(fAkun);
    exit(0);
}

void changePassword(int Indexakun)
{
    FILE *fAkun, *fTempAkun;
    fAkun = fopen("akunPass.txt","r");
    fTempAkun = fopen("tempAkun.txt","w");

    char newPassword[20], oldPassword[20];
    int i = 1;

    printf("MASUKAN PASSWORD BARU :");
    gets(newPassword);

    if (strlen(newPassword) < 5)
    {
        system("cls");
        printf("HARAP LEBIH DARI 5 KARAKTER!\n");
        changePassword(Indexakun);
    }
    printf("%s",newPassword);

    while (!feof(fAkun))
    {
        fscanf(fAkun,"%s", oldPassword);
        if (i == Indexakun)
        {
            fprintf(fTempAkun,"%s\n",newPassword);
        }
        else{
            fprintf(fTempAkun, "%s\n", oldPassword);
        }
        i++;
    }

    fclose(fAkun);
    fclose(fTempAkun);
    remove("akunPass.txt");
    rename("tempAkun.txt", "akunPass.txt");
}