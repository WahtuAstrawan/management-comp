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
    AdminDeleteAccount(),
    addAcc(char *jabatan, char *username, char *password);

int main()
{

    login();

    return 0;
}

void login()
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    fungsi ini digunakan untuk login akun
    kemudian memanggil subprogram sesuai
    dengan jabatan akun tersebut
*/ 
{
    //system("cls");
    char usernameInserted[21];
    char subprogram[8];
    while (1)
    {
        printf("Masukan Username Anda\n");
        printf(">> ");
        gets(usernameInserted);

        if (checkPassword(usernameInserted, subprogram))// melakukan pengencekan password akun tersebut
        {
            if (!strcmp(subprogram, "admin"))// sub program admin
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "kasir"))// sub program kasir
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "gudang"))// sub program gudang
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "manager"))// sub program manager
            {
                AdminSubProgram();
            }

            printf("ada sub program tidak diketahui");// hanya untuk berjaga jaga saat ada subprogram aneh yang masuk
            exit(0);
        }
    }
}

int checkPassword(char *usernameInserted, char *jabatan)
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    fungsi ini digunakan untuk mengecek password
    dari akun yang diinput sekaligus ketersedian
    akun

    parameter :
    usernameInserted (username yang diinputkan)
    jabatan (pada fungsi ini, akan dimasukkan jabatan akun tersebut)

    return :
    1 (password benar)
    0 (akun tidak ada)
*/ 
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    - prosedur ini merupakan sub program admin
    - prosedur ini akan dipanggil saat ada username jabatan admin login
    - memiliki 3 wewenang, membuat, mengedit, dan menghapus akun
    - prosedur ini akan memanggil prosedur sesuai pilihan user
*/ 
{
    int Pilihan;
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| [1] Buat Akun                            ||\n");
    printf("|| [2] Edit Akun                            ||\n");
    printf("|| [3] Hapus Akun                           ||\n");
    printf("|| [4] log out                              ||\n");
    printf("||                       [0] Keluar Program ||\n");
    printf("||                                          ||\n");
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
        AdminEditAccount();
        exit(0);
        break;
    case 3:
        AdminDeleteAccount();
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


void AdminCreateAccount()
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    - prosedur ini akan membuat sebuah akun
    - prosedur ini meminta user memilih jabatan baru
    - prosedur ini meminta user memasukan username dan password baru
    - Data akun baru akan ditambahkan ke akunPass.txt
*/ 
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
    }
    addAcc(jabatan, username, password);

    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| Buat Akun Lainnya?                       ||\n");
    printf("|| [0] Tidak                                ||\n");
    printf("|| [1] Iya                                  ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&ulang, 0, 1, "  >> ");
    if (ulang == 1)
    {
        AdminCreateAccount();
    }
    else if (ulang == 0)
    {
        AdminSubProgram();
    }
    else{
        printf("\nerror\n");
        exit(0);
    }
}
void AdminEditAccount()
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    -   prosedur ini akan mengedit akun sesuai dengan masukan user
    -   menu edit yaitu mengganti jabatan, username, dan password
    -   prosedur ini akan membuat sebuah file tempAkun.txt untuk
        memasukkan data file baru kemudian tempAkun akan
        berubah menjadi akunPass.txt
*/ 
{
    int Pilihan;
    int ulang;
    int status;

    char newVariable[21];
    char akun[1080];

    char jabatan[8];
    char username[21];
    char password[21];

    // program meminta user menginput username yang ingin di edit
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf(" Masukan Username Akun Yang Ingin Di Edit\n");
    printf(" (ketik 0 untuk kembali ke menu admin)\n");
    while (1) // validasi akun yang akan di edit
    {
        gets(akun);
        printf(" >> ");

        if (!strcmp(akun, "0"))
        {
            AdminSubProgram();
            exit(0);
        }
        else if (!strcmp(akun, "admin"))
        {
            printf("\t\t\tadmin tidak bisa diedit!\n");
            continue;
        }
        else if (cekUser(akun))
        {
            break;
        }
        printf("\t\t\tAkun Tidak Ada!\n");
    }

    while (1)
    {

        // memilih menu edit akun
        status = 0;
        system("cls");
        printf("==============================================\n");
        printf("...............SUB PROGRAM ADMIN..............\n");
        printf("==============================================\n");
        printf("  Username :%s\n", akun);
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
            if (gantiJabatan(newVariable))
            {
                status++;
            }
            break;
        case 2:
            if (gantiUsername(newVariable))
            {
                status++;
            }
            break;
        case 3:
            if (gantiPassword(newVariable))
            {
                status++;
            }
            break;
        case 0:
            AdminEditAccount();
            break;
        default:
            break;
        }

        if (status != 0)
        {
            continue;
        }

        FILE *fAkun, *fTempAkun;
        fAkun = fopen("akunPass.txt", "r");
        fTempAkun = fopen("tempAkun.txt", "w");
        do
        {
            fscanf(fAkun, "%[^,],%[^,],%[^\n]\n", jabatan, username, password);
            if (!strcmp(username, akun))
            {
                switch (Pilihan)
                {
                case 1:
                    fprintf(fTempAkun, "%s,%s,%s\n", newVariable, username, password);
                    break;
                case 2:
                    fprintf(fTempAkun, "%s,%s,%s\n", jabatan, newVariable, password);
                    strcpy(akun, newVariable);
                    break;
                case 3:
                    fprintf(fTempAkun, "%s,%s,%s\n", jabatan, username, newVariable);
                    break;
                default:
                    break;
                }
            }
            else
            {
                fprintf(fTempAkun, "%s,%s,%s\n", jabatan, username, password);
            }

        } while (!feof(fAkun));

        fclose(fAkun);
        fclose(fTempAkun);
        remove("akunPass.txt");
        rename("tempAkun.txt", "akunPass.txt");

        system("cls");
        printf("==============================================\n");
        printf("...............SUB PROGRAM ADMIN..............\n");
        printf("==============================================\n");
        printf("  Username :%s\n", akun);
        printf("==============================================\n");
        printf("||                                          ||\n");
        printf("|| Tetap Mengedit Akun Ini?                 ||\n");
        printf("|| [0] Tidak                                ||\n");
        printf("|| [1] Iya                                  ||\n");
        printf("||                                          ||\n");
        printf("==============================================\n");
        range_int(&ulang, 0, 1, ">> ");
        if (ulang == 1)
        {
            continue;
        }
        break;
    }
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| Edit Akun Lainnya?                      ||\n");
    printf("|| [0] Tidak                                ||\n");
    printf("|| [1] Iya                                  ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&ulang, 0, 1, "  >> ");
    if (ulang == 1)
    {
        AdminEditAccount();
    }
    else if (ulang == 0)
    {
        AdminSubProgram();
    }
    else{
        printf("\nerror\n");
        exit(0);
    }
}
void AdminDeleteAccount()
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan : 
    -   prosedur ini akan menghapus akun yang dimasukkan user
    -   prosedur ini akan membuat sebuah file tempAkun.txt untuk
        memasukkan data file baru kemudian tempAkun akan
        berubah menjadi akunPass.txt
*/ 
{
    char jabatan[8];
    char username[21];
    char password[21];

    char akun[1080];
    int ulang;

    // program meminta user menginput username yang ingin di hapus
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf(" Masukan Username Akun Yang Ingin Di Edit\n");
    printf(" (ketik 0 untuk kembali ke menu admin)\n");
    while (1) // validasi ketersedian akun yang akan di hapus
    {
        printf(" >> ");
        gets(akun);

        if (!strcmp(akun, "0"))
        {
            AdminSubProgram();
            exit(0);
        }
        else if (!strcmp(akun, "admin"))
        {
            printf("\t\t\tadmin tidak bisa dihapus!\n");
            continue;
        }
        else if (cekUser(akun))
        {
            break;
        }
        printf("\t\t\tAkun Tidak Ada!\n");
    }

    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("  Username : %s\n", akun);
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| Anda Yakin Menghapus Akun Ini?           ||\n");
    printf("|| [0] Tidak                                ||\n");
    printf("|| [1] Iya                                  ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&ulang, 0, 1, "  >> ");
    if (ulang == 0)
    {
        AdminDeleteAccount();
    }

    FILE *fAkun, *fTempAkun;
    fAkun = fopen("akunPass.txt", "r");
    fTempAkun = fopen("tempAkun.txt", "w");
    do
    {
        fscanf(fAkun, "%[^,],%[^,],%[^\n]\n", jabatan, username, password);
        if (strcmp(akun, username))
        {
            fprintf(fTempAkun, "%s,%s,%s\n", jabatan, username, password);
        }
    } while (!feof(fAkun));

    fclose(fAkun);
    fclose(fTempAkun);
    remove("akunPass.txt");
    rename("tempAkun.txt", "akunPass.txt");

    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| Hapus Akun Lainnya?                      ||\n");
    printf("|| [0] Tidak                                ||\n");
    printf("|| [1] Iya                                  ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&ulang, 0, 1, "  >> ");
    if (ulang == 1)
    {
        AdminDeleteAccount();
    }
    else if (ulang == 0)
    {
        AdminSubProgram();
    }
    else{
        printf("\nerror\n");
        exit(0);
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
