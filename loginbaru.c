#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLOR_OFF "\e[m"
#define RED "\033[31m"

int checkPassword(char *usernameInserted, char *jabatan),
    inputUsername(char *user),
    cekUser(char *nama),
    inputPassword(char *pass),
    gantiJabatan(char *newJabatan),
    gantiUsername(char *newUsername),
    gantiPassword(char *newPassword);
void login(),
    AdminSubProgram(),
    range_int(int *var, int range1, int range2, char *intruksi),
    input_int(int *var, char *intruksi),
    AdminCreateAccount(),
    AdminEditAccount(),
    addAcc(char *jabatan, char *username, char *password);

int main(int argc, char const *argv[])
{

    login();

    return 0;
}

void login()
{
    // system("cls");
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
                    fclose(fAkun);
                    login();
                }
                else if (!strcmp(password, passwordInserted))
                {
                    fclose(fAkun);
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
    fclose(fAkun);
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
        AdminEditAccount();
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
    int ulang;

    char jabatan[8];
    char username[21];
    char password[21];

    if (gantiJabatan(jabatan))
    {
        AdminSubProgram();
    }

    // // memilih jabatan akun yang akan dibuat
    // system("cls");
    // printf("==============================================\n");
    // printf("...............SUB PROGRAM ADMIN..............\n");
    // printf("==============================================\n");
    // printf("||            Tentukan Jabatan Akun         ||\n");
    // printf("||                                          ||\n");
    // printf("|| [1] Kasir                                ||\n");
    // printf("|| [2] Gudang                               ||\n");
    // printf("|| [3] Manager                              ||\n");
    // printf("||                              [0] Kembali ||\n");
    // printf("==============================================\n");
    // range_int(&Pilihan, 0, 3, ">> ");

    // // masukan username akun yang akan dibuat
    // switch (Pilihan)
    // {
    // case 1:
    //     strcpy(jabatan, "kasir");
    //     break;
    // case 2:
    //     strcpy(jabatan, "gudang");
    //     break;

    // case 3:
    //     strcpy(jabatan, "manager");
    //     break;

    // case 0:
    //     AdminSubProgram();
    //     break;
    // default:
    //     printf("pilihan menu terdapat angka diluar menu\n");
    //     break;
    // }

    while (1)
    {
        system("cls");
        printf("==============================================\n");
        printf("...............SUB PROGRAM ADMIN..............\n");
        printf("==============================================\n");
        printf("     Jabatan : %s                          \n", jabatan);
        printf("==============================================\n");
        printf("||                                          ||\n");
        printf("||   Format Username :                      ||\n");
        printf("||   1. Hanya Berupa Angka                  ||\n");
        printf("||   2. Terdiri dari Minimal 5 karakter     ||\n");
        printf("||      dan maksimal 20 karakter            ||\n");
        printf("||                                          ||\n");
        printf("||                 Masukan 0 untuk kembali  ||\n");
        printf("==============================================\n");
        if (inputUsername(username))
        {
            AdminCreateAccount();
            exit(0);
        }

        // masukan password akun yang akan dibuat
        system("cls");
        printf("==============================================\n");
        printf("...............SUB PROGRAM ADMIN..............\n");
        printf("==============================================\n"); ///:
        printf("     Jabatan  : %s                          \n", jabatan);
        printf("     Username : %s                          \n", username);
        printf("==============================================\n");
        printf("||                                          ||\n");
        printf("||   Format Password :                      ||\n");
        printf("||      Terdiri dari Minimal 8 karakter     ||\n");
        printf("||      dan maksimal 20 karakter            ||\n");
        printf("||                                          ||\n");
        printf("||                 Masukan 0 untuk kembali  ||\n");
        printf("==============================================\n");
        if (inputPassword(password))
        {
            continue;
        }
        break;
    }

    while (1)
    {
        // masukan password akun yang akan dibuat
        system("cls");
        printf("==============================================\n");
        printf("...............SUB PROGRAM ADMIN..............\n");
        printf("==============================================\n"); ///:
        printf("     Jabatan  : %s                          \n", jabatan);
        printf("     Username : %s                          \n", username);
        printf("     Password : %s                          \n", password);
        printf("==============================================\n");
        printf("  [1]Buat Akun                     [0]ulang \n");
        range_int(&ulang, 0, 1, " >> ");
        if (ulang == 1)
        {
            break;
        }
        else if (ulang == 0)
        {
            AdminCreateAccount();
            exit(0);
        }
        else
        {
            continue;
        }
    };
    addAcc(jabatan, username, password);
}
void AdminEditAccount()
{
    int Pilihan;
    int ulang;
    int status;

    char newVariable[21];
    char akun[21];

    char jabatan[8];
    char username[21];
    char password[21];

    // program meminta user menginput username yang ingin di edit
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf(" Masukan Username Akun Yang Ingin Di Edit\n");
    printf(" (ketik 0 untuk kembali)\n");
    printf(" >> \n");
    while (1) // validasi akun yang akan di edit
    {
        gets(akun);

        if (!strcmp(akun, "0"))
        {
            AdminSubProgram();
            exit(0);
        }
        else if (!strcmp(akun, "admin"))
        {
            printf("\t\t\tadmin tidak bisa diedit!");
            continue;
        }
        else if (cekUser(akun))
        {
            break;
        }
        printf("\t\t\tAkun Tidak Ada!");
    }

    // memilih menu edit akun
    status = 0;
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("  Username :%s\n",akun);
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| [1] Ganti Jabatan Akun                   ||\n");
    printf("|| [2] Ganti Username                       ||\n");
    printf("|| [3] Ganti Password                       ||\n");
    printf("||                              [0] Kembali ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 3, ">> ");
    
    switch (Pilihan)
    {
    case 1:
        gantiJabatan(newVariable);
        break;
    case 2:
        gantiPassword(newVariable);
        break;
    case 3:
        gantiPassword(newVariable);
        break;
    case 0:
        AdminEditAccount();
        break;

    default:
        break;
    }
}

int inputUsername(char *user)
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
        if (!strcmp(newUsername, "0"))
        {
            return 1;
        }

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

        if (cekUser(newUsername))
        {
            printf("\t\tUsername Sudah Digunakan!!\n\n");
            continue;
        }

        if (status == 0)
        {
            break;
        }
    }

    strcpy(user, newUsername);
    return 0;
}

int cekUser(char *nama)
{
    char jabatan[21];
    char password[21];
    char username[20];

    FILE *fAkun = fopen("akunPass.txt", "r");

    do
    {
        fscanf(fAkun, "%[^,],%[^,],%[^\n]\n", jabatan, username, password);
        if (!strcmp(username, nama))
        {

            fclose(fAkun);
            return 1;
        }
    } while (!feof(fAkun));

    fclose(fAkun);
    return 0;
}

int inputPassword(char *pass)
{
    char newPassword[21], confirm[21];
    int status;
    while (1)
    {
        status = 0;
        printf("  Masukan Password anda\n  >> ");
        // printf("  >> ");
        fflush(stdin);
        gets(newPassword);
        if (!strcmp(newPassword, "0"))
        {
            return 1;
        }

        if (strlen(newPassword) > 20 || strlen(newPassword) < 8)
        {
            printf("\t\tpassword invalid\n");
            continue;
        }

        while (1)
        {
            printf("  Konfirmasi Password\n  >> ");

            fflush(stdin);
            gets(confirm);
            if (!strcmp(confirm, "0"))
            {
                status++;
                break;
                ;
            }
            else if (strcmp(confirm, newPassword))
            {
                printf("\t\tPassword Tidak Sama!\n\n");
                continue;
            }
            break;
        }

        if (status == 0)
        {
            break;
        }
    }
    strcpy(pass, newPassword);
    return 0;
}

void addAcc(char *jabatan, char *username, char *password)
{
    FILE *fAkun = fopen("akunPass.txt", "a");

    fprintf(fAkun, "%s,%s,%s\n", jabatan, username, password);
    fclose(fAkun);
}

int gantiJabatan(char *newJabatan)
{
    int Pilihan;
    // memilih jabatan akun yang akan dibuat
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||        Tentukan Jabatan Baru Akun        ||\n");
    printf("||                                          ||\n");
    printf("|| [1] Kasir                                ||\n");
    printf("|| [2] Gudang                               ||\n");
    printf("|| [3] Manager                              ||\n");
    printf("||                              [0] Kembali ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 3, ">> ");
    switch (Pilihan)
    {
    case 1:
        strcpy(newJabatan, "kasir");
        break;
    case 2:
        strcpy(newJabatan, "gudang");
        break;
    case 3:
        strcpy(newJabatan, "manager");
        break;
    case 0:
        return 1;
        break;

    default:
        printf("oops\n");
        break;
    }

    return 0;
}
int gantiPassword(char *newPassword)
{

    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("||   Format Password :                      ||\n");
    printf("||      Terdiri dari Minimal 8 karakter     ||\n");
    printf("||      dan maksimal 20 karakter            ||\n");
    printf("||                                          ||\n");
    printf("||                 Masukan 0 untuk kembali  ||\n");
    printf("==============================================\n");
    if (inputPassword(newPassword))
    {
        return 1;
    }
    return 0;
}
int gantiUsername(char *newUsername)
{
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("||   Format Username :                      ||\n");
    printf("||   1. Hanya Berupa Angka                  ||\n");
    printf("||   2. Terdiri dari Minimal 5 karakter     ||\n");
    printf("||      dan maksimal 20 karakter            ||\n");
    printf("||                                          ||\n");
    printf("||                 Masukan 0 untuk kembali  ||\n");
    printf("==============================================\n");
    if (inputUsername(newUsername))
    {
        return 1;
        exit(0);
    }
    return 0;
}
