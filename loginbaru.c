#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int checkPassword(char *usernameInserted, char *jabatan),
    InputUsername(char *user);
void login(),
    AdminSubProgram(),
    range_int(int *var, int range1, int range2, char *intruksi),
    input_int(int *var, char *intruksi),
    AdminCreateAccount();

int main(int argc, char const *argv[])
{

    login();

    return 0;
}

void login()
{
    system("cls");
    char usernameInserted[21];
    char subprogram[8];
    while (1)
    {
        printf("Masukan Username Anda\n");
        printf(">> ");
        gets(usernameInserted);

        if (checkPassword(usernameInserted, subprogram))
        {
            if (!strcmp(subprogram, "admin"))
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "kasir"))
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "gudang"))
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "manager"))
            {
                AdminSubProgram();
            }

            printf("ada sub program tidak diketahui");
            exit(0);
        }
    }
}

int checkPassword(char *usernameInserted, char *jabatan)
{
    char passwordInserted[21];
    char password[21];
    char username[20];

    FILE *fAkun = fopen("akunPass.txt", "r");
    if (fAkun == NULL) // buat file password defult
    {
        fclose(fAkun);
        fAkun = fopen("akunPass.txt", "w");
        fprintf(fAkun, "admin,admin,admin\n");
        fclose(fAkun);
        fAkun = fopen("akunPass.txt", "r");
    }

    do
    {
        fscanf(fAkun, "%[^,],%[^,],%[^\n]\n", jabatan, username, password);

        if (!strcmp(username, usernameInserted))
        {
            while (1)
            {
                printf("MASUKAN PASSWORD ANDA\n");
                printf("(ketik 0 untuk kembali mengisi username)\n");
                printf(">> ");
                gets(passwordInserted);
                if (!strcmp(passwordInserted, "0"))
                {
                    login();
                }
                else if (!strcmp(password, passwordInserted))
                {
                    return 1;
                }
                else
                {
                    printf("password salah!\n");
                }
            }
        }

    } while (!feof(fAkun));
    printf("username tidak ditemukan!\n");
    return 0;
}

void AdminSubProgram()
{
    int Pilihan;
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("|| [1] Buat Akun                            ||\n");
    printf("|| [2] Hapus Akun                           ||\n");
    printf("|| [3] Edit Akun                            ||\n");
    printf("|| [4] log out                              ||\n");
    printf("||                               [0] Keluar ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 4, ">> ");
    switch (Pilihan)
    {
    case 0:
        exit(0);
        break;
    case 1:
        AdminCreateAccount();
        exit(0);
        break;
    case 2:
        exit(0);
        break;
    case 3:
        exit(0);
        break;
    case 4:
        login();
        exit(0);
        break;

    default:
        printf("pilihan menu terdapat angka diluar menu\n");
        break;
    }
    exit(0);
}

void input_int(int *var, char *intruksi) //
{
    char buff[1024];
    char cek;

    while (1)
    {
        printf("%s", intruksi);
        fflush(stdin);
        if (fgets(buff, sizeof(buff), stdin) != NULL)
        {
            if (sscanf(buff, "%d %c", var, &cek) == 1)
            {
                break;
            }
        }
        printf("\t\t\t Input salah! Silahkan coba lagi\n");
    }
}
void range_int(int *var, int range1, int range2, char *intruksi) // membatasi input
{
    while (1)
    {
        input_int(var, intruksi);
        fflush(stdin);
        if (*var >= range1 && *var <= range2)
            break;
        printf("Harap Memilih Menu yang Tersedia!\n");
    }
}

void AdminCreateAccount()
{
    int Pilihan;
    char jabatan[8];
    char username[21];
    char password[21];

    // memilih jabatan akun yang akan dibuat
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||            Tentukan Jabatan Akun         ||\n");
    printf("||                                          ||\n");
    printf("|| [1] Kasir                                ||\n");
    printf("|| [2] Gudang                               ||\n");
    printf("|| [3] Manager                              ||\n");
    printf("||                              [0] Kembali ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 4, ">> ");

    // masukan username akun yang akan dibuat
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n"); ///:
    switch (Pilihan)
    {
    case 1:
        printf("||                Akun Kasir                 ||\n");
        strcpy(jabatan, "kasir");
        break;
    case 2:
        printf("||                Akun Gudang               ||\n");
        strcpy(jabatan, "gudang");
        break;

    case 3:
        printf("||               Akun Manager               ||\n");
        strcpy(jabatan, "manager");
        break;

    case 0:
        AdminSubProgram();
        break;
    default:
        printf("pilihan menu terdapat angka diluar menu\n");
        break;
    }

    printf("||                                          ||\n");
    printf("||   Format Username :                      ||\n");
    printf("||   1. Hanya Berupa Angka                  ||\n");
    printf("||   1. Terdiri dari Minimal 8 karakter     ||\n");
    printf("||   1. dan maksimal 20 karakter            ||\n");
    printf("||                                          ||\n");
    printf("||                   masuk 0 untuk Kembali  ||\n");
    printf("==============================================\n");
    printf("  Masukan Username anda\n");
    printf("  >> ");
}

int InputUsername(char *user)
{
    char newUsername[21];
    int i, status;
    while (1)
    {
        i = 0;
        status = 0;
        printf("  Masukan Username anda\n");
        printf("  >> ");

        fflush(stdin);
        gets(newUsername);
        if (strlen(newUsername) > 20 || strlen(newUsername) < 5)
        {
            printf("\t\tUsername Invalid!!\n\n");
            continue;
        }

        while (newUsername[i])
        {
            if (!isalpha(newUsername[i]))
            {
                printf("\t\tUsername Invalid!!\n\n");
                status++;
                break;
            }
            i++;
        }
        if (status == 0)
        {
            break;
        }
    }
    
    strcpy(user,newUsername);
    return 0;
}