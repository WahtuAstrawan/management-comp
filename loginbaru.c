#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

    managerSubProgram(),
    managerShowAccount(),
    showAllAcc(),
    managerOften(),
    managerProfit(),
    managerOften(),

    editTempHis(char *barang, int jumlah),
    sortTemphis(),
    hapusTempSort(char *barangTarget),

    addAcc(char *jabatan, char *username, char *password),
    date(int *tanggal, int *bulan, int *tahun),
    positif_int(int *var, char *intruksi);

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
    // system("cls");
    char usernameInserted[21];
    char subprogram[8];
    while (1)
    {
        printf("Masukan Username Anda\n");
        printf(">> ");
        gets(usernameInserted);

        if (checkPassword(usernameInserted, subprogram)) // melakukan pengencekan password akun tersebut
        {
            if (!strcmp(subprogram, "admin")) // sub program admin
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "kasir")) // sub program kasir
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "gudang")) // sub program gudang
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "manager")) // sub program manager
            {
                managerSubProgram();
            }

            printf("ada sub program tidak diketahui"); // hanya untuk berjaga jaga saat ada subprogram aneh yang masuk
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
    else
    {
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
    else
    {
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
    else
    {
        printf("\nerror\n");
        exit(0);
    }
}

int inputUsername(char *user)
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk membuat username baru
        sekaligus memvalidasinya
    -   validasinya berupa karakter 5-20, huruf saja, dan
        bersifat unik

    parameter :
    -   char *user => untuk tempat ditampungnya username yang baru

    return :
    -   1 => jika user memasukkan "0" (berfungsi kembali)
    -   0 => validasi sukses
*/
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk mengecek apakah
        username baru unik (tidak sama dengan username lain)

    parameter :
    -   char *nama => calon username baru

    return :
    -   1 => terdapat username yang sama
    -   0 => calon username unik
*/
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk membuat password baru
        sekaligus memvalidasinya
    -   terdapat kofirmasi password
    -   validasinya berupa karakter 8-20

    parameter :
    -   char *user => untuk tempat ditampungnya password yang baru

    return :
    -   1 => jika user memasukkan "0" (berfungsi kembali)
    -   0 => validasi sukses
*/
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   prosedur ini digunakan untuk menambahkan akun
        yang terdiri dari jabatan, username, dan password
    -   data disimpan di akunPass.txt

    parameter :
    -   char *jabatan => jabatan dari akun yang ditambahkan
    -   char *username => username dari akun yang ditambahkan
    -   char *password => password dari akun yang ditambahkan
*/
{
    FILE *fAkun = fopen("akunPass.txt", "a");

    fprintf(fAkun, "%s,%s,%s\n", jabatan, username, password);
    fclose(fAkun);
}

int gantiJabatan(char *newJabatan)
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk menampilkan dan menyimpan
        pilihan jabatan untuk akun
    -   digunakan saat membuat akun dan mengedit akun

    parameter :
    -   char *newJabatan => untuk tempat ditampungnya jabatan yang baru

    return :
    -   1 => jika user memasukkan "0" (berfungsi kembali)
    -   0 => pilihan disimpan sementara
*/
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk membuat password baru
        sekaligus menampilkan format password
    -   digunakan saat membuat akun dan mengedit akun

    parameter :
    -   char *newPassword => untuk tempat ditampungnya password yang baru

    return :
    -   1 => jika user memasukkan "0" (berfungsi kembali)
    -   0 => pilihan disimpan sementara
*/
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
/*  Pembuat : Liangga
    Tanggal : 14/12/2022
    Revisi  : -

    Catatan :
    -   fungsi ini digunakan untuk membuat username baru
        sekaligus menampilkan format username
    -   digunakan saat mengedit akun

    parameter :
    -   char *newUsername => untuk tempat ditampungnya username yang baru

    return :
    -   1 => jika user memasukkan "0" (berfungsi kembali)
    -   0 => pilihan disimpan sementara
*/
{
    system("cls");
    printf("==============================================\n");
    printf("...............SUB PROGRAM ADMIN..............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("||             Masukan Username             ||\n");
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
void positif_int(int *var, char *intruksi)
{
    while (1)
    {
        input_int(var, intruksi);
        fflush(stdin);
        if (*var >= 0)
            break;
        printf("\t\t\tInput Tidak Valid\n");
    }
}

void managerSubProgram()
{
    int Pilihan;
    system("cls");
    printf("==============================================\n");
    printf("..............SUB PROGRAM MANAGER.............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| [1] Daftar Pegawai                       ||\n");
    printf("|| [2] Pemasukan kotor                      ||\n");
    printf("|| [3] Barang Paling Laku                   ||\n");
    printf("|| [4] log out                              ||\n");
    printf("||                       [0] Keluar Program ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 4, ">> ");
    switch (Pilihan)
    {
    case 1:
        managerShowAccount();
        exit(0);
        break;
    case 2:
        managerProfit();
        exit(0);
        break;
    case 3:
        managerOften();
        exit(0);
        break;
    case 4:
        login();
        exit(0);
        break;

    default:
        break;
    }
}

void managerShowAccount()
{
    int Pilihan;
    FILE *fAkun = fopen("akunPass.txt", "r");
    int kasir = 0, gudang = 0, manager = 0;

    char jabatan[8];
    char username[21];
    char password[21];

    do
    {
        fscanf(fAkun, " %[^,],%[^,],%[^\n]\n", jabatan, username, password);
        if (!strcmp(jabatan, "kasir"))
        {
            kasir++;
        }
        else if (!strcmp(jabatan, "gudang"))
        {
            gudang++;
        }
        else if (!strcmp(jabatan, "manager"))
        {
            manager++;
        }
    } while (!feof(fAkun));

    fclose(fAkun);
    system("cls");
    printf("==============================================\n");
    printf("..............SUB PROGRAM MANAGER.............\n");
    printf("==============================================\n");
    printf("  Pegawai Saat ini berjumlah %d Pegawai\n", kasir + manager + gudang);
    printf("    - Kasir   : %d Orang\n", kasir);
    printf("    - Gudang  : %d Orang\n", gudang);
    printf("    - Manager : %d Orang\n", manager);
    printf("==============================================\n");
    printf("  [1]Lihat Semua Akun               [0]Kembali\n");
    range_int(&Pilihan, 0, 1, ">> ");
    switch (Pilihan)
    {
    case 1:
        system("cls");
        printf("==============================================\n");
        printf("..............SUB PROGRAM MANAGER.............\n");
        printf("==============================================\n");
        printf("  Pegawai Saat ini berjumlah %d Pegawai\n", kasir + manager + gudang);
        printf("    - Kasir : %d Orang\n", kasir);
        printf("    - Gudang : %d Orang\n", gudang);
        printf("    - Manager : %d Orang\n", manager);
        printf("==============================================\n");
        showAllAcc();
        range_int(&Pilihan, 0, 0, ">> ");
    case 0:
        managerSubProgram();
        exit(0);
        break;

    default:
        break;
    }
}
void showAllAcc()
{
    FILE *fAkun;
    char jabatan[8],
        username[21],
        password[21];
    int pp = 0;
    for (int i = 0; i < 3; i++)
    {
        fAkun = fopen("akunPass.txt", "r");
        while (!feof(fAkun))
        {
            fscanf(fAkun, "%[^,],%[^,],%[^\n]\n", jabatan, username, password);
            switch (i)
            {
            case 0:
                if (!strcmp(jabatan, "kasir"))
                {
                    printf("      %s \t(%s)\n", username, jabatan);
                }

                break;
            case 1:
                if (!strcmp(jabatan, "gudang"))
                {
                    printf("      %s \t(%s)\n", username, jabatan);
                }
                break;
            case 2:
                if (!strcmp(jabatan, "manager"))
                {
                    printf("      %s \t(%s)\n", username, jabatan);
                }
                break;

            default:
                break;
            }
        }
    }
    printf("==============================================\n");
    printf("  [0]Kembali\n");

    fclose(fAkun);
}

void managerProfit()
{
    FILE *fHis = fopen("riwayatpembelian.txt", "r");
    int tanggal,
        bulan,
        bulanLalu,
        tahun,
        dateHis,
        monHis,
        yearHis,
        jumlahBarang,
        harga;
    long int totalHarga = 0;
    char barang[100];

    date(&tanggal, &bulan, &tahun);

    printf("%d %d %d\n", tanggal, bulan, tahun);
    system("pause");
    // printf("%d\n",tahun);

    int Pilihan;
    system("cls");
    printf("==============================================\n");
    printf("..............SUB PROGRAM MANAGER.............\n");
    printf("==============================================\n");
    printf("||                                          ||\n");
    printf("|| [1] Pemasukan Bulan Ini                  ||\n");
    printf("|| [2] Pemasukan Bulan Lalu                 ||\n");
    printf("||                             [0] Kembali  ||\n");
    printf("||                                          ||\n");
    printf("==============================================\n");
    range_int(&Pilihan, 0, 2, ">> ");

    switch (Pilihan)
    {
    case 1:
        system("cls");
        printf("==============================================\n");
        printf("..............SUB PROGRAM MANAGER.............\n");
        printf("==============================================\n");
        printf("  Pemasukan %d/%d\n", bulan, tahun);
        break;
    case 2:
        system("cls");
        printf("==============================================\n");
        printf("..............SUB PROGRAM MANAGER.............\n");
        printf("==============================================\n");
        printf("||                                          ||\n");
        printf("||     Berapa Bulan Kebelakang?             ||\n");
        printf("||                                          ||\n");
        printf("||                             [0] Kembali  ||\n");
        printf("||                                          ||\n");
        printf("==============================================\n");
        positif_int(&bulanLalu, ">> ");
        if (bulanLalu == 0)
        {
            managerProfit();
            exit(0);
        }
        bulan -= bulanLalu % 12;
        tahun -= bulanLalu / 12;
        system("cls");
        printf("==============================================\n");
        printf("..............SUB PROGRAM MANAGER.............\n");
        printf("==============================================\n");
        printf("  Pemasukan %d/%d\n", bulan, tahun);
        break;
    case 3:
        managerSubProgram();
        break;

    default:
        break;
    }
    do
    {
        fscanf(fHis, "%d,%d,%d,%[^,],%d,%d\n", &dateHis, &monHis, &yearHis, barang, &jumlahBarang, &harga);
        if (bulan == monHis && tahun == yearHis)
        {
            totalHarga += harga;
        }

    } while (!feof(fHis));

    printf("\t RP. %d", totalHarga);
    printf("\n  PPN  : Rp. %.1f\n", (((float)totalHarga) * 0.11));
    fclose(fHis);
    printf("\n==============================================\n");
    printf("  [1]kembali                         [0]Menu\n");
    range_int(&Pilihan, 0, 1, " >> ");
    switch (Pilihan)
    {
    case 1:
        managerProfit();
        exit(0);
        break;
    case 0:
        managerSubProgram();
        exit(0);
        break;
    default:
        break;
    }
}

void managerOften()
{

    int tanggal,
        bulan,
        bulanLalu,
        tahun,
        dateHis,
        monHis,
        yearHis,
        jumlahBarang,
        jumlahtarget,
        harga;
    char barang[100],
        barangTarget[100];

    date(&tanggal, &bulan, &tahun);

    int pertama = 0,
        i,
        status,
        data[1080];

    FILE *fHis = fopen("riwayatpembelian.txt", "r"),
         *read,
         *app = fopen("riwayatpembelianTemp.txt", "a");

    do
    {

        fscanf(fHis, "%d,%d,%d,%[^,],%d,%d\n", &dateHis, &monHis, &yearHis, barang, &jumlahBarang, &harga);
        if (bulan == monHis && tahun == yearHis)
        {

            if (pertama == 0)
            {

                fprintf(app, "%s,%d\n", barang, jumlahBarang);
                fclose(app);
                pertama++;
            }
            else
            {
                status = 0;
                read = fopen("riwayatpembelianTemp.txt", "r");
                do
                {
                    fscanf(read, "%[^,],%d\n", barangTarget, &jumlahtarget);
                    if (!strcmp(barang, barangTarget))
                    {
                        fclose(read);
                        editTempHis(barang, jumlahBarang);
                        status++;
                        break;
                    }

                } while (!feof(read));
                if (status == 0)
                {

                    fclose(read);
                    app = fopen("riwayatpembelianTemp.txt", "a");
                    fprintf(app, "%s,%d\n", barang, jumlahBarang);
                    fclose(app);
                }
            }
        }
    } while (!feof(fHis));

    
    // app = fopen("sortTemp.txt", "w");

    // sampe sini tanggal 16
    // fscanf(read, "%[^,],%d\n", barang, &jumlahBarang);

    // strcpy(barangTarget, barang);
    // jumlahtarget = jumlahBarang;
    // do
    // {
    //     fscanf(read, "%[^,],%d\n", barang, &jumlahBarang);
    //     if (jumlahBarang > jumlahtarget)
    //     {
    //         strcpy(barangTarget, barang);
    //         jumlahtarget = jumlahBarang;
    //     }
    // } while (!feof(read));
    // printf("%s,%d", barangTarget, jumlahtarget);

    
    // system("pause");
    sortTemphis();

    //minjem variable untuk ngeprint ini aja
    read = fopen("riwayatpembelianTemp.txt", "r");
    printf("==============================================\n");
    printf("..............SUB PROGRAM MANAGER.............\n");
    printf("==============================================\n");
    do
    {
        fscanf(read,"%[^,],%d\n",barangTarget,&jumlahtarget);
        printf("  - %s  (%d Unit)\n",barangTarget,jumlahtarget);
    } while (!feof(read));
    fclose(read);
    remove("riwayatpembelianTemp.txt");

    exit(0);
}

void editTempHis(char *barang, int jumlah)
{
    FILE *Read = fopen("riwayatpembelianTemp.txt", "r"),
         *Add = fopen("TempEditHis.txt", "w");

    char barangTarget[100];
    int jumlahTarget;

    while (!feof(Read))
    {
        fscanf(Read, "%[^,],%d\n", barangTarget, &jumlahTarget);

        if (!strcmp(barang, barangTarget))
        {
            jumlahTarget += jumlah;
            fprintf(Add, "%s,%d\n", barangTarget, jumlahTarget);
        }
        else
        {
            fprintf(Add, "%s,%d\n", barangTarget, jumlahTarget);
        }
    }
    fclose(Add);
    fclose(Read);
    remove("riwayatpembelianTemp.txt");
    rename("TempEditHis.txt", "riwayatpembelianTemp.txt");
}

void date(int *tanggal, int *bulan, int *tahun)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *tanggal = tm.tm_mday;
    *bulan = tm.tm_mon + 1;
    *tahun = tm.tm_year + 1900;
}

void sortTemphis()
{
    char barang[100], barangHigh[100];
    int jumlah, jumlahHigh;
    FILE *read, *add;

    read = fopen("riwayatpembelianTemp.txt", "r");
    add = fopen("sortTemp.txt", "a");

    fscanf(read, "%[^,],%d\n", barang, &jumlah);

    strcpy(barangHigh, barang);
    jumlahHigh = jumlah;
    do
    {
        fscanf(read, "%[^,],%d\n", barang, &jumlah);
        if (jumlah > jumlahHigh)
        {
            //printf("%s,%d\n", barang, jumlah);
            strcpy(barangHigh, barang);
            jumlahHigh = jumlah;
        }
    } while (!feof(read));

    fprintf(add, "%s,%d\n", barangHigh, jumlahHigh);
    fclose(add);
    fclose(read);


    strerror(errno);
    //system("pause");
    hapusTempSort(barangHigh);

    read = fopen("riwayatpembelianTemp.txt", "r");
    if (read != NULL)
    {
        fclose(read);
        sortTemphis();
    }
    fclose(read);
    rename("sortTemp.txt","riwayatpembelianTemp.txt");
}
void hapusTempSort(char *barangTarget)
{
    FILE *read = fopen("riwayatpembelianTemp.txt", "r"),
         *write = fopen("TempHapusHis.txt", "w");

    char barang[100];
    int jumlah,
        status = 0;
    do
    {
        fflush(stdin);
        fscanf(read, "%[^,],%d\n", barang, &jumlah);
        if (strcmp(barangTarget, barang))
        {
            //printf("%s,%d\n", barang, jumlah);
            fprintf(write, "%s,%d\n", barang, jumlah);
            status++;
        }
    } while (!feof(read));
    fclose(write);
    fclose(read);

    //printf("hapus\n");
    remove("riwayatpembelianTemp.txt");
    rename("TempHapusHis.txt", "riwayatpembelianTemp.txt");


    if (status == 0)
    {
        remove("riwayatpembelianTemp.txt");
    }
}
