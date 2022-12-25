// Menginclude Library yang akan digunakan
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Mendefinisikan untuk warna dan style dari text dan besar dari pajak PPN
#define COLOR_OFF "\e[m"
#define RED "\033[31m"
#define PPN 0.11

// Pendeklarasian semua fungsi
void intro(), awalCashier(), awalGudang(), menulistBarang(char *aksi), prosesBarang(char *namaFile, char *aksi),
    hapusBarang(char *namaFile), editBarang(char *namaFile), totalTransaksi(), tambahBarang(char *kategori, char *namaFile),
    stokHabis(), pesanSalah(), daftarBarang(), input_int(int *var, char *intruksi), range_int(int *var, int range1, int range2, char *intruksi),
    input_yakin(char *var), login(),
    AdminSubProgram(),
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

int cobaLagiG(char *aksi), konfirmasiBarang(char *nama, char *harga, char *stok), checkPassword(char *usernameInserted, char *jabatan),
    inputUsername(char *user), cekUser(char *nama), inputPassword(char *pass), gantiJabatan(char *newJabatan), gantiUsername(char *newUsername),
    gantiPassword(char *newPassword);

// Pendeklarasian Semua Variabel dan Struct Global
FILE *fp, *fp2, *fptemp;
int n = 0, jenisLogin;
typedef struct Barang
{
    char *nama[100];
    char *harga[15];
    char *stok[15];
} barang[100], gudang[100];

typedef struct Beli
{
    char *nama[100];
    char *namaFile[30];
    int harga;
    int jumlah;
    int totalHarga;
} transaksi[100];

transaksi x;

// Program Utama/Main
int main()
{
    intro();
    return 0;
}

void intro()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 10/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan tampilan
        nama program pada saat program dibuka
    */
    system("cls");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||>>>>>>>>>>>>>>> COMPUTER MANAGEMENT <<<<<<<<<<<<<<||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\n\t\t\t\t           Tekan enter untuk melanjutkan....");
    getchar();
    login();
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
    system("cls");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||>>>>>>>>>>>>>>>>>> LOGIN ACCOUNT <<<<<<<<<<<<<<<<<||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ======================================================\n");
    char usernameInserted[21];
    char subprogram[8];
    while (1)
    {

        printf("\t\t\t\t Masukan Username Anda\n");
        printf("\t\t\t\t >> ");
        gets(usernameInserted);

        if (checkPassword(usernameInserted, subprogram)) // melakukan pengencekan password akun tersebut
        {
            if (!strcmp(subprogram, "admin")) // sub program admin
            {
                AdminSubProgram();
            }
            else if (!strcmp(subprogram, "kasir")) // sub program kasir
            {
                awalCashier();
            }
            else if (!strcmp(subprogram, "gudang")) // sub program gudang
            {
                awalGudang();
            }
            else if (!strcmp(subprogram, "manager")) // sub program manager
            {
                managerSubProgram();
            }

            printf("\t\t\t\tada sub program tidak diketahui"); // hanya untuk berjaga jaga saat ada subprogram aneh yang masuk
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
                printf("\n\t\t\t\t Masukan Password Anda\n");
                printf("\t\t\t\t (ketik 0 untuk kembali mengisi username)\n");
                printf("\t\t\t\t >> ");
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
                    printf(RED "\t\t\t\t\t\tpassword salah!\n" COLOR_OFF);
                }
            }
        }

    } while (!feof(fAkun));
    printf(RED "\t\t\t\t\t\tusername tidak ditemukan!\n\n" COLOR_OFF);
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| [1] Buat Akun                            ||\n");
    printf("\t\t\t\t|| [2] Edit Akun                            ||\n");
    printf("\t\t\t\t|| [3] Hapus Akun                           ||\n");
    printf("\t\t\t\t|| [4] log out                              ||\n");
    printf("\t\t\t\t||                       [0] Keluar Program ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&Pilihan, 0, 4, "\t\t\t\t>> ");
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
        printf("\t\t\t\tpilihan menu terdapat angka diluar menu\n");
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
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t     Jabatan : %s                          \n", jabatan);
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||   Format Username :                      ||\n");
        printf("\t\t\t\t||   1. Hanya Berupa Angka                  ||\n");
        printf("\t\t\t\t||   2. Terdiri dari Minimal 5 karakter     ||\n");
        printf("\t\t\t\t||      dan maksimal 20 karakter            ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||                 Masukan 0 untuk kembali  ||\n");
        printf("\t\t\t\t==============================================\n");
        if (inputUsername(username))
        {
            AdminCreateAccount();
            exit(0);
        }

        // masukan password akun yang akan dibuat
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
        printf("\t\t\t\t==============================================\n"); ///:
        printf("\t\t\t\t     Jabatan  : %s                          \n", jabatan);
        printf("\t\t\t\t     Username : %s                          \n", username);
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||   Format Password :                      ||\n");
        printf("\t\t\t\t||      Terdiri dari Minimal 8 karakter     ||\n");
        printf("\t\t\t\t||      dan maksimal 20 karakter            ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||                 Masukan 0 untuk kembali  ||\n");
        printf("\t\t\t\t==============================================\n");
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
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t     Jabatan  : %s                          \n", jabatan);
        printf("\t\t\t\t     Username : %s                          \n", username);
        printf("\t\t\t\t     Password : %s                          \n", password);
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  [1]Buat Akun                     [0]ulang \n");
        range_int(&ulang, 0, 1, "\t\t\t\t>> ");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| Buat Akun Lainnya?                       ||\n");
    printf("\t\t\t\t|| [0] Tidak                                ||\n");
    printf("\t\t\t\t|| [1] Iya                                  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&ulang, 0, 1, "\t\t\t\t>> ");
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
        printf("\t\t\t\t\nerror\n");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t Masukan Username Akun Yang Ingin Di Edit\n");
    printf("\t\t\t\t (ketik 0 untuk kembali ke menu admin)");
    while (1) // validasi akun yang akan di edit
    {

        printf("\n\t\t\t\t >> ");
        gets(akun);

        if (!strcmp(akun, "0"))
        {
            AdminSubProgram();
            exit(0);
        }
        else if (!strcmp(akun, "admin"))
        {
            printf(RED "\n\t\t\t\t\t\tadmin tidak bisa diedit!\n" COLOR_OFF);
            continue;
        }
        else if (cekUser(akun))
        {
            break;
        }
        printf(RED "\n\t\t\t\t\t\tAkun Tidak Ada!\n" COLOR_OFF);
    }

    while (1)
    {

        // memilih menu edit akun
        status = 0;
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  Username :%s\n", akun);
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t|| [1] Ganti Jabatan Akun                   ||\n");
        printf("\t\t\t\t|| [2] Ganti Username                       ||\n");
        printf("\t\t\t\t|| [3] Ganti Password                       ||\n");
        printf("\t\t\t\t||                              [0] Kembali ||\n");
        printf("\t\t\t\t==============================================\n");
        range_int(&Pilihan, 0, 3, "\t\t\t\t>> ");

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
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  Username :%s\n", akun);
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t|| Tetap Mengedit Akun Ini?                 ||\n");
        printf("\t\t\t\t|| [0] Tidak                                ||\n");
        printf("\t\t\t\t|| [1] Iya                                  ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t==============================================\n");
        range_int(&ulang, 0, 1, "\t\t\t\t>> ");
        if (ulang == 1)
        {
            continue;
        }
        break;
    }
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| Edit Akun Lainnya?                      ||\n");
    printf("\t\t\t\t|| [0] Tidak                                ||\n");
    printf("\t\t\t\t|| [1] Iya                                  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&ulang, 0, 1, "\t\t\t\t>> ");
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
        printf("\t\t\t\t\nerror\n");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t Masukan Username Akun Yang Ingin Di Edit\n");
    printf("\t\t\t\t (ketik 0 untuk kembali ke menu admin)");
    while (1) // validasi ketersedian akun yang akan di hapus
    {
        printf("\n\t\t\t\t >> ");
        gets(akun);

        if (!strcmp(akun, "0"))
        {
            AdminSubProgram();
            exit(0);
        }
        else if (!strcmp(akun, "admin"))
        {
            printf(RED "\n\t\t\t\t\t\tadmin tidak bisa dihapus!\n" COLOR_OFF);
            continue;
        }
        else if (cekUser(akun))
        {
            break;
        }
        printf(RED "\n\t\t\t\t\t\tAkun Tidak Ada!\n" COLOR_OFF);
    }

    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  Username : %s\n", akun);
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| Anda Yakin Menghapus Akun Ini?           ||\n");
    printf("\t\t\t\t|| [0] Tidak                                ||\n");
    printf("\t\t\t\t|| [1] Iya                                  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&ulang, 0, 1, "\t\t\t\t>> ");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| Hapus Akun Lainnya?                      ||\n");
    printf("\t\t\t\t|| [0] Tidak                                ||\n");
    printf("\t\t\t\t|| [1] Iya                                  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&ulang, 0, 1, "\t\t\t\t>> ");
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
        printf("\t\t\t\t\nerror\n");
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
        printf("\t\t\t\t  Masukan Username anda\n");
        printf("\t\t\t\t  >> ");

        fflush(stdin);
        gets(newUsername);
        if (!strcmp(newUsername, "0"))
        {
            return 1;
        }

        if (strlen(newUsername) > 20 || strlen(newUsername) < 5)
        {
            printf(RED "\t\t\t\t\t\tUsername Invalid!!\n\n" COLOR_OFF);
            continue;
        }

        while (newUsername[i])
        {
            if (!isalpha(newUsername[i]))
            {
                printf(RED "\t\t\t\t\t\tUsername Invalid!!\n\n" COLOR_OFF);
                status++;
                break;
            }
            i++;
        }

        if (cekUser(newUsername))
        {
            printf(RED "\t\t\t\t\t\tUsername Sudah Digunakan!!\n\n" COLOR_OFF);
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
        printf("\t\t\t\t  Masukan Password anda\n\t\t\t\t>> ");
        // printf("\t\t\t\t  >> ");
        fflush(stdin);
        gets(newPassword);
        if (!strcmp(newPassword, "0"))
        {
            return 1;
        }

        if (strlen(newPassword) > 20 || strlen(newPassword) < 8)
        {
            printf(RED "\t\t\t\t\t\tpassword invalid\n" COLOR_OFF);
            continue;
        }

        while (1)
        {
            printf("\t\t\t\t  Konfirmasi Password\n\t\t\t\t>> ");

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
                printf(RED "\t\t\t\t\t\tPassword Tidak Sama!\n\n" COLOR_OFF);
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
    -   dipanggil di AdminCreateAccount()
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||        Tentukan Jabatan Baru Akun        ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| [1] Kasir                                ||\n");
    printf("\t\t\t\t|| [2] Gudang                               ||\n");
    printf("\t\t\t\t|| [3] Manager                              ||\n");
    printf("\t\t\t\t||                              [0] Kembali ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&Pilihan, 0, 3, "\t\t\t\t>> ");
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
        printf("\t\t\t\toops\n");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t||   Format Password :                      ||\n");
    printf("\t\t\t\t||      Terdiri dari Minimal 8 karakter     ||\n");
    printf("\t\t\t\t||      dan maksimal 20 karakter            ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t||                 Masukan 0 untuk kembali  ||\n");
    printf("\t\t\t\t==============================================\n");
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t...............SUB PROGRAM ADMIN..............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t||             Masukan Username             ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t||   Format Username :                      ||\n");
    printf("\t\t\t\t||   1. Hanya Berupa Angka                  ||\n");
    printf("\t\t\t\t||   2. Terdiri dari Minimal 5 karakter     ||\n");
    printf("\t\t\t\t||      dan maksimal 20 karakter            ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t||                 Masukan 0 untuk kembali  ||\n");
    printf("\t\t\t\t==============================================\n");
    if (inputUsername(newUsername))
    {
        return 1;
        exit(0);
    }
    return 0;
}

void positif_int(int *var, char *intruksi)
{
    while (1)
    {
        input_int(var, intruksi);
        fflush(stdin);
        if (*var >= 0)
            break;
        printf(RED "\t\t\t\t\t\t\tInput Tidak Valid\n" COLOR_OFF);
    }
}

void managerSubProgram()
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini merupakan sub program manager
    -   memiliki 3 menu yaitu daftar pegawai, pemasukan kotor, trend barang
*/
{
    int Pilihan;
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| [1] Daftar Pegawai                       ||\n");
    printf("\t\t\t\t|| [2] Pemasukan kotor                      ||\n");
    printf("\t\t\t\t|| [3] Trend Barang                         ||\n");
    printf("\t\t\t\t|| [4] log out                              ||\n");
    printf("\t\t\t\t||                       [0] Keluar Program ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&Pilihan, 0, 4, "\t\t\t\t>> ");
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
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk menampilkan jumlah pegawai dengan jabatannya
    -   digunakan saat mengedit akun
*/
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
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  Pegawai Saat ini berjumlah %d Pegawai\n", kasir + manager + gudang);
    printf("\t\t\t\t    - Kasir   : %d Orang\n", kasir);
    printf("\t\t\t\t    - Gudang  : %d Orang\n", gudang);
    printf("\t\t\t\t    - Manager : %d Orang\n", manager);
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  [1]Lihat Semua Akun               [0]Kembali\n");
    range_int(&Pilihan, 0, 1, "\t\t\t\t>> ");
    switch (Pilihan)
    {
    case 1:
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  Pegawai Saat ini berjumlah %d Pegawai\n", kasir + manager + gudang);
        printf("\t\t\t\t    - Kasir : %d Orang\n", kasir);
        printf("\t\t\t\t    - Gudang : %d Orang\n", gudang);
        printf("\t\t\t\t    - Manager : %d Orang\n", manager);
        printf("\t\t\t\t==============================================\n");
        showAllAcc();
        range_int(&Pilihan, 0, 0, "\t\t\t\t>> ");
    case 0:
        managerSubProgram();
        exit(0);
        break;

    default:
        break;
    }
}

void showAllAcc()
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk menampilkan daftar pegawai secara keseluruhan
    -   dipanggil didalam prosedur managerShowAccount()
*/
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
            switch (i) // agar di akun ditampilkan secara terurut berdasarkan jabatan
            {
            case 0:
                if (!strcmp(jabatan, "kasir"))
                {
                    printf("\t\t\t\t      %s \t(%s)\n", username, jabatan);
                }

                break;
            case 1:
                if (!strcmp(jabatan, "gudang"))
                {
                    printf("\t\t\t\t      %s \t(%s)\n", username, jabatan);
                }
                break;
            case 2:
                if (!strcmp(jabatan, "manager"))
                {
                    printf("\t\t\t\t      %s \t(%s)\n", username, jabatan);
                }
                break;

            default:
                break;
            }
        }
    }
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  [0]Kembali\n");

    fclose(fAkun);
}

void managerProfit()
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk menampilkan keuntungan pada bulan tertentu
        yang dipilih user
*/
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

    int Pilihan;
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| [1] Pemasukan Bulan Ini                  ||\n");
    printf("\t\t\t\t|| [2] Pemasukan Bulan Lalu                 ||\n");
    printf("\t\t\t\t||                             [0] Kembali  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&Pilihan, 0, 2, "\t\t\t\t>> ");

    switch (Pilihan)
    {
    case 1:
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  Pemasukan %d/%d\n", bulan, tahun);
        break;
    case 2:
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||     Berapa Bulan Kebelakang?             ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||                             [0] Kembali  ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t==============================================\n");
        positif_int(&bulanLalu, "\t\t\t\t>> ");
        if (bulanLalu == 0)
        {
            managerProfit();
            exit(0);
        }
        bulan -= bulanLalu % 12;
        tahun -= bulanLalu / 12;
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t  Pemasukan %d/%d\n", bulan, tahun);
        break;
    case 0:
        managerSubProgram();
        break;

    default:
        break;
    }

    // mulai proses penghitungan
    do
    {
        fscanf(fHis, "%d,%d,%d,%[^,],%d,%d\n", &dateHis, &monHis, &yearHis, barang, &jumlahBarang, &harga);
        if (bulan == monHis && tahun == yearHis)
        {
            totalHarga += harga;
        }

    } while (!feof(fHis));

    printf("\t\t\t\t\t RP. %d\n", totalHarga);
    printf("\t\t\t\t\t  PPN  : Rp. %.1f\n", (((float)totalHarga) * 0.11));
    fclose(fHis);
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  [1]kembali                         [0]Menu\n");
    range_int(&Pilihan, 0, 1, "\t\t\t\t>> ");
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
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk menampilkan ranking barang yang sering dibeli(trend barang)
        pada bulan tertentu yang dipilih user
*/

{

    int tanggal,
        bulan,
        bulanLalu,
        tahun,
        dateHis,
        monHis,
        yearHis,
        jumlahBarang, // menampung jumlah barang didalam riwayatpembelian.txt
        jumlahtarget, // menamapung jumlah barang didalam riwayatpembelianTemp.txt
        harga;
    char barang[100],      // menampung nama barang didalam riwayatpembelian.txt
        barangTarget[100]; // menamapung nama barang didalam riwayatpembelianTemp.txt

    date(&tanggal, &bulan, &tahun);

    int Pilihan;
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t|| [1] Trend Bulan Ini                      ||\n");
    printf("\t\t\t\t|| [2] Trend Bulan Lalu                     ||\n");
    printf("\t\t\t\t||                             [0] Kembali  ||\n");
    printf("\t\t\t\t||                                          ||\n");
    printf("\t\t\t\t==============================================\n");
    range_int(&Pilihan, 0, 2, "\t\t\t\t>> ");

    switch (Pilihan)
    {
    case 1:
        break;
    case 2:
        system("cls");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
        printf("\t\t\t\t==============================================\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||     Berapa Bulan Kebelakang?             ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t||                             [0] Kembali  ||\n");
        printf("\t\t\t\t||                                          ||\n");
        printf("\t\t\t\t==============================================\n");
        positif_int(&bulanLalu, "\t\t\t\t>> ");
        if (bulanLalu == 0)
        {
            managerOften();
            exit(0);
        }
        bulan -= bulanLalu % 12;
        tahun -= bulanLalu / 12;

        break;
    case 0:
        managerSubProgram();
        break;

    default:
        break;
    }
    system("cls");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t..............SUB PROGRAM MANAGER.............\n");
    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  Trend Barang %d/%d\n", bulan, tahun);

    // mulai proses
    int pertama = 0, trend = 0,
        status;

    FILE *fHis = fopen("riwayatpembelian.txt", "r"),
         *read,
         *app = fopen("riwayatpembelianTemp.txt", "a");

    while (!feof(fHis))
    {
        fscanf(fHis, "%d,%d,%d,%[^,],%d,%d\n", &dateHis, &monHis, &yearHis, barang, &jumlahBarang, &harga);
        if (bulan == monHis && tahun == yearHis) // hanya menerima data barang di tanggal yang ditentukan
        {

            if (pertama == 0) // data pertama akan langsung dicatat di file Temp
            {

                fprintf(app, "%s,%d\n", barang, jumlahBarang);
                fclose(app);
                pertama++; // acuan bahwa data pertama sudah dicatat
            }
            else
            {
                status = 0;
                read = fopen("riwayatpembelianTemp.txt", "r");
                while (!feof(read))
                {
                    fscanf(read, "%[^,],%d\n", barangTarget, &jumlahtarget);

                    // memeriksa apakah ada nama barang yang sama antara di file riwayatpembelian.txt dengan riwayatpembelianTemp.txt
                    if (!strcmp(barang, barangTarget))
                    {
                        fclose(read);
                        editTempHis(barang, jumlahBarang); // jika sama, edit jumlah barang tersebut
                        status++;                          // acuan bahwa ada nama barang yang sama
                        break;
                    }
                }
                if (status == 0) // jika tidak ada nama barang sama, catat data barang tersebut
                {

                    fclose(read);
                    app = fopen("riwayatpembelianTemp.txt", "a");
                    fprintf(app, "%s,%d\n", barang, jumlahBarang);
                    fclose(app);
                }
            }
            trend++; // untuk acuan apakah ada pembelian di tanggal yang sudah ditentukan
        }
    }

    fclose(fHis);
    if (trend == 0)
    {
        fclose(app);
        printf("\n\t\t\t\t\tBulan Ini Tidak Ada Pembelian\n");
    }
    else
    {
        sortTemphis();

        // minjem variable untuk ngeprint ini aja
        read = fopen("riwayatpembelianTemp.txt", "r");
        do
        {
            fscanf(read, "%[^,],%d\n", barangTarget, &jumlahtarget);
            printf("\t\t\t\t  - %s\t(%d Unit)\n", barangTarget, jumlahtarget);
        } while (!feof(read));
        fclose(read);
    }
    remove("riwayatpembelianTemp.txt");

    printf("\t\t\t\t==============================================\n");
    printf("\t\t\t\t  [1]Ulang                           [0]Menu\n");
    range_int(&Pilihan, 0, 1, "\t\t\t\t>> ");
    if (Pilihan == 1)
    {
        managerOften();
        exit(0);
    }
    else
    {
        managerSubProgram();
        exit(0);
    }
}

void date(int *tanggal, int *bulan, int *tahun)
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk mengetahui local time saat program dijalankan
    parameter :
    int *tanggal
    int *bulan
    int *tahun
*/
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *tanggal = tm.tm_mday;
    *bulan = tm.tm_mon + 1;
    *tahun = tm.tm_year + 1900;
}

void editTempHis(char *barang, int jumlah)
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk merubah jumlah barang dari file riwayatpembelianTemp.txt
    -   prosedur ini dipanggil di prosedur managerOften()
    parameter :
    -   char *barang => untuk tempat ditampungnya nama barang yang ingin dirubah
    -   int jumlah   => untuk menampung jumlah barang
*/
{
    // membuka file yang diperlukan
    FILE *Read = fopen("riwayatpembelianTemp.txt", "r"),
         *Add = fopen("TempEditHis.txt", "w");

    char barangTarget[100]; // menampung data barang di dalam file
    int jumlahTarget;       // menampung jumlah barang di dalam file

    while (!feof(Read))
    {
        // membaca file per baris
        fscanf(Read, "%[^,],%d\n", barangTarget, &jumlahTarget);

        if (!strcmp(barang, barangTarget)) // saat nama barang disuatu baris sama dengan barang yang ingin diubah jumlahnya
        {
            jumlahTarget += jumlah; // tambah jumlah barang semula dengan jumlah barang yang dimasukkan di parameter
            fprintf(Add, "%s,%d\n", barangTarget, jumlahTarget);
        }
        else // selain itu catat data barang ke TempEditHis.txt
        {
            fprintf(Add, "%s,%d\n", barangTarget, jumlahTarget);
        }
    }
    fclose(Add);
    fclose(Read);
    remove("riwayatpembelianTemp.txt");
    rename("TempEditHis.txt", "riwayatpembelianTemp.txt");
}

void sortTemphis()
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk mengurutkan secara descending file riwayatpembelianTemp.txt
        dengan teknik rekursif kemudian menyimpannya secara sementara di sortTemp.txt
        setelah semua data terurut sortTemp.txt akan direname menjadi riwayatpembelianTemp.txt
    -   prosedur ini dipanggil di dalam prosedur managerOften()
*/
{
    char barang[100],    // menampung data nama barang
        barangHigh[100]; // menampung nama barang yang memiliki jumlah tertinggi
    int jumlah,          // menampung data jumlah barang
        jumlahHigh;      // menampung jumlah barang tertinggi

    FILE *read, *add;
    read = fopen("riwayatpembelianTemp.txt", "r");
    add = fopen("sortTemp.txt", "a");

    // menjadikan data pertama sebagai data barang tertinggi
    fscanf(read, "%[^,],%d\n", barang, &jumlah);
    strcpy(barangHigh, barang);
    jumlahHigh = jumlah;

    while (!feof(read))
    {
        fscanf(read, "%[^,],%d\n", barang, &jumlah);
        if (jumlah > jumlahHigh) // membandingkan jumlah barang suatu baris dengan jumlah tertinggi
        {

            strcpy(barangHigh, barang); // mengganti nama dan jumlah barang tertinggi
            jumlahHigh = jumlah;
        }
    }

    fprintf(add, "%s,%d\n", barangHigh, jumlahHigh); // data tertinggi simpan di sortTemp
    fclose(add);
    fclose(read);

    hapusTempSort(barangHigh); // data barang tertinggi akan dihapus di file riwayatpembelianTemp.txt

    read = fopen("riwayatpembelianTemp.txt", "r");
    if (read != NULL) // jika ada data selain data tertinggi, akan dicari data tertinggi kedua, ketiga dst
    {
        fclose(read);
        sortTemphis();
    }
    fclose(read);
    rename("sortTemp.txt", "riwayatpembelianTemp.txt");
}

void hapusTempSort(char *barangTarget)
/*  Pembuat : Liangga
    Tanggal : 15/12/2022
    Revisi  : -
    Catatan :
    -   prosedur ini digunakan untuk menghapus suatu data di riwayatpembelianTemp.txt
        jika sudah dicatat di sortTemp.txt
    -   prosedur ini dipanggil di dalam prosedur sortTemphis()
    parameter :
    -   char *barangTarget => untuk tempat ditampungnya nama barang yang ingin dihapus
*/
{
    // membuka file yang dibutuhkan
    FILE *read = fopen("riwayatpembelianTemp.txt", "r"),
         *write = fopen("TempHapusHis.txt", "w");

    char barang[100];
    int jumlah,
        status = 0; // sebagai acuan apakah program memasuki perulangan
    while (!feof(read))
    {
        fflush(stdin);
        fscanf(read, "%[^,],%d\n", barang, &jumlah);
        if (strcmp(barangTarget, barang)) // tulis data barang selain data barang yang ingin dihapus
        {

            fprintf(write, "%s,%d\n", barang, jumlah);
            status++;
        }
    }
    fclose(write);
    fclose(read);

    remove("riwayatpembelianTemp.txt");
    rename("TempHapusHis.txt", "riwayatpembelianTemp.txt");

    if (status == 0) // saat tidak ada data (tidak memasuki perulangan) maka hapus file riwayatpembelian.txt
    {
        remove("riwayatpembelianTemp.txt");
    }
}

void awalCashier()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 10/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan tampilan
        dan menu cashier pada saat login atau masuk sebagai cashier
        yang didalamnya dapat melakukan transaksi costumer
    */
    system("cls");
    jenisLogin = 11;
    int pilih;
    char yakin;
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||.............. CASHIER TRANSACTIONS ..............||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t || Pilihan ||              MAIN MENU                ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [1]   ||  Transaksi Costumer                   ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [2]   ||  Logout                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [3]   ||  Keluar                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    range_int(&pilih, 1, 3, "\t\t\t\t  Pilihan (1/2/3) \n\t\t\t\t  >> ");
    if (pilih == 1)
    {
        menulistBarang("Transaksi");
    }
    else if (pilih == 2)
    {
        system("cls");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin logout ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            login();
        }
        else if (yakin == 'X')
        {
            awalCashier();
        }
    }
    else
    {
        system("cls");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin keluar ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            exit(0);
        }
        else if (yakin == 'X')
        {
            awalCashier();
        }
    }
}

void awalGudang()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 10/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan tampilan
        dan menu gudang pada saat login atau masuk sebagai gudang
        yang didalamnya terdapat pilihan untuk tambah, edit, dan hapus data barang
    */
    system("cls");
    jenisLogin = 22;
    n = 0;
    int pilih;
    char yakin;
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||................ WAREHOUSE ACTIVITY ..............||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t || Pilihan ||              MAIN MENU                ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [1]   ||  Tambah Data Barang                   ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [2]   ||  Edit Data Barang                     ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [3]   ||  Hapus Data Barang                    ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [4]   ||  Logout                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ||   [5]   ||  Keluar                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    range_int(&pilih, 1, 5, "\t\t\t\t  Pilihan (1/2/3/4/5) \n\t\t\t\t  >> ");
    if (pilih == 1)
    {
        jenisLogin += 1;
        menulistBarang("Ditambah");
    }
    else if (pilih == 2)
    {
        jenisLogin += 2;
        menulistBarang("Diedit");
    }
    else if (pilih == 3)
    {
        jenisLogin += 3;
        menulistBarang("Dihapus");
    }
    else if (pilih == 4)
    {
        system("cls");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin logout ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            login();
        }
        else if (yakin == 'X')
        {
            awalGudang();
        }
    }
    else
    {
        system("cls");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin keluar ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            exit(0);
        }
        else if (yakin == 'X')
        {
            awalGudang();
        }
    }
}

void menulistBarang(char *aksi)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 10/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan kategori barang
        yang tersedia untuk melakukan transaksi maupun aktifitas gudang
        Parameter : aksi (digunakan untuk memberikan instruksi proses apa yang akan dijalankan pada pilihan menu)
    */
    int pilih;
    system("cls");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||................ LIST JENIS BARANG ...............||\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t || Pilihan ||            NAMA JENIS BARANG          ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [1]   || Processor                             ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [2]   || GPU                                   ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [3]   || RAM                                   ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [4]   || Keyboard                              ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [5]   || Mouse                                 ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [6]   || Monitor                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [7]   || Headset                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [8]   || Motherboard                           ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [9]   || Harddisk                              ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||  [10]   || Casing PC                             ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||  [11]   || Lainnya                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||   [0]   || Kembali                               ||\n");
    printf("\t\t\t\t ||         ||                                       ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t  Pilihan jenis barang untuk %s (1 -> 11) dan 0 untuk kembali \n", aksi);
    printf("\t\t\t\t  Atau Pilih 12 untuk Mengkonfirmasi Pembelian (bila ada) \n");
    range_int(&pilih, 0, 12, "\t\t\t\t  >> ");
    if (pilih == 0)
    {
        if (jenisLogin == 11)
        {
            awalCashier();
        }
        else if (jenisLogin >= 22 && jenisLogin <= 25)
        {
            awalGudang();
        }
    }
    else if (pilih == 1)
    {
        prosesBarang("prosesor.txt", "Prosesor");
    }
    else if (pilih == 2)
    {
        prosesBarang("gpu.txt", "GPU");
    }
    else if (pilih == 3)
    {
        prosesBarang("ram.txt", "RAM");
    }
    else if (pilih == 4)
    {
        prosesBarang("keyboard.txt", "Keyboard");
    }
    else if (pilih == 5)
    {
        prosesBarang("mouse.txt", "Mouse");
    }
    else if (pilih == 6)
    {
        prosesBarang("monitor.txt", "Monitor");
    }
    else if (pilih == 7)
    {
        prosesBarang("headset.txt", "Headset");
    }
    else if (pilih == 8)
    {
        prosesBarang("mboard.txt", "Motherboard");
    }
    else if (pilih == 9)
    {
        prosesBarang("memory.txt", "Harddisk");
    }
    else if (pilih == 10)
    {
        prosesBarang("case.txt", "Casing PC");
    }
    else if (pilih == 11)
    {
        prosesBarang("lainnya.txt", "Lainnya");
    }
    else if (pilih == 12)
    {
        if (n > 0)
        {
            n--;
            totalTransaksi();
        }
        else
        {
            pesanSalah();
            menulistBarang(aksi);
        }
    }
    else
    {
        pesanSalah();
        menulistBarang(aksi);
    }
}

void prosesBarang(char *namaFile, char *aksi)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 11/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan barang
        yang tersedia pada kategori barang tertentu untuk melakukan transaksi
        dan juga melakukan aktifitas gudang tergantung dari jenis masuk/login
        Parameter :
        namaFile (digunakan untuk menentukan kategori dan isi barang mana yang akan ditampilkan dan diproses)
        aksi (digunakan untuk memberikan instruksi tentang jenis barang apa yang diproses)
    */
    if (jenisLogin == 11)
    {
        barang a;
        int pilih, jumlah, stok;
        char yakin;
        int i = 0, read, no = 1;
        fp = fopen(namaFile, "r");
        do
        {
            system("cls");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", a[i].nama, a[i].harga, a[i].stok);
                printf("\t\t\t\t ||             || %s                                      \n", a[i].nama);
                printf("\t\t\t\t ||     [%d]     || Harga/unit   : Rp.%s,-                  \n", no, a[i].harga);
                printf("\t\t\t\t ||             || Jumlah Stok  : %s                       \n", a[i].stok);
                printf("\t\t\t\t ==========================================================\n");
                no++;
                i++;
            } while (!feof(fp));
            fclose(fp);
            printf("\t\t\t\t Pilihan anda ( 1 -> %d ) atau Pilih 0 untuk kembali \n", no - 1);
            range_int(&pilih, 0, no - 1, "\t\t\t\t >> ");
            if (pilih == 0)
            {
                menulistBarang("Transaksi");
            }
            else if (pilih >= 1 && pilih <= no)
            {
                pilih -= 1;
                stok = atoi(a[pilih].stok);
                if (stok > 0)
                {
                    jumlah = konfirmasiBarang(a[pilih].nama, a[pilih].harga, a[pilih].stok);
                    if (jumlah > 0)
                    {
                        *x[n].nama = a[pilih].nama;
                        x[n].harga = atoi(a[pilih].harga);
                        x[n].jumlah = jumlah;
                        x[n].totalHarga = (x[n].harga * x[n].jumlah);
                        *x[n].namaFile = namaFile;
                        break;
                    }
                    else
                    {
                        prosesBarang(namaFile, aksi);
                    }
                }
                else if (stok <= 0)
                {
                    stokHabis();
                    pilih -= 999;
                    continue;
                }
            }
            else
            {
                pesanSalah();
            }
        } while (pilih < 0 || pilih > no);
        system("cls");
        printf("\t\t\t\t =========================================================\n");
        printf("\t\t\t\t ||        Apakah Anda Ingin membeli barang lagi ?      ||\n");
        printf("\t\t\t\t =========================================================\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            n++;
            menulistBarang("Transaksi");
        }
        else if (yakin == 'X')
        {
            totalTransaksi();
            awalCashier();
        }
    }
    else if (jenisLogin == 23)
    {
        tambahBarang(aksi, namaFile);
    }
    else if (jenisLogin == 24)
    {
        editBarang(namaFile);
    }
    else if (jenisLogin == 25)
    {
        hapusBarang(namaFile);
    }
}

void hapusBarang(char *namaFile)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 12/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menghapus data barang yang ada pada file
        dengan nama sesuai dengan parameter namaFile
        Parameter :
        namaFile (digunakan untuk menentukan file kategori barang mana yang akan dihapus datanya)
    */
    gudang z;
    char namaR[100], hargaR[15], stokR[15];
    int pilih, read, cobalagi;
    char yakin;
    do
    {
        while (true)
        {
            system("cls");
            int i = 0, no = 1;
            fp = fopen(namaFile, "r");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", z[i].nama, z[i].harga, z[i].stok);
                printf("\t\t\t\t ||             || %s                                      \n", z[i].nama);
                printf("\t\t\t\t ||     [%d]     || Harga/unit   : Rp.%s,-                  \n", no, z[i].harga);
                printf("\t\t\t\t ||             || Jumlah Stok  : %s                        \n", z[i].stok);
                printf("\t\t\t\t ==========================================================\n");
                no++;
                i++;
            } while (!feof(fp));
            fclose(fp);
            printf("\t\t\t\t Pilih data yang akan dihapus ( 1 -> %d ) atau ( 0 untuk kembali ) \n", no - 1);
            range_int(&pilih, 0, no - 1, "\t\t\t\t >> ");
            if (pilih == 0)
            {
                menulistBarang("Dihapus");
            }
            else if (pilih >= 1 && pilih <= no)
            {
                pilih -= 1;
                system("cls");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||               Data yang anda pilih               ||\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t || Nama Barang             : %s\n", z[pilih].nama);
                printf("\t\t\t\t || Harga per unit          : Rp.%s,-\n", z[pilih].harga);
                printf("\t\t\t\t || Sisa Stok               : %s\n", z[pilih].stok);
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||     Apakah anda ingin menghapus data diatas ?    ||\n");
                printf("\t\t\t\t ======================================================\n");
                input_yakin(&yakin);
                if (yakin == 'Y')
                {
                    break;
                }
                else if (yakin == 'X')
                {
                    continue;
                }
            }
            else
            {
                pesanSalah();
            }
        }
        fp = fopen(namaFile, "r");
        fptemp = fopen("temp.txt", "w");
        do
        {
            read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", namaR, hargaR, stokR);
            if (read == 3)
            {
                if (strcmp(z[pilih].nama, namaR) == 0)
                {
                    continue;
                }
                else
                {
                    fprintf(fptemp, "%s,%s,%s\n", namaR, hargaR, stokR);
                }
            }
        } while (!feof(fp));
        fclose(fp);
        fclose(fptemp);
        remove(namaFile);
        rename("temp.txt", namaFile);
        system("cls");
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t ||          Data telah berhasil dihapus  !       ||\n");
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t           Tekan enter untuk melanjutkan...");
        getchar();
        cobalagi = cobaLagiG("Menghapus data");
    } while (cobalagi == 1);
    awalGudang();
}

void editBarang(char *namaFile)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 13/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk mengedit data barang yang ada pada file
        dengan nama sesuai dengan parameter namaFile
        Parameter :
        namaFile (digunakan untuk menentukan file kategori barang mana yang akan diedit datanya)
    */
    gudang y;
    char namaBaru[100], hargaBaru[15], stokBaru[15];
    char namaR[100], hargaR[15], stokR[15];
    int pilihEdit;
    int pilih, read, cobalagi;
    char yakin;
    do
    {
        while (true)
        {
            system("cls");
            int i = 0, no = 1;
            fp = fopen(namaFile, "r");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", y[i].nama, y[i].harga, y[i].stok);
                printf("\t\t\t\t ||             || %s                                       \n", y[i].nama);
                printf("\t\t\t\t ||     [%d]     || Harga/unit   : Rp.%s,-                  \n", no, y[i].harga);
                printf("\t\t\t\t ||             || Jumlah Stok  : %s                        \n", y[i].stok);
                printf("\t\t\t\t ==========================================================\n");
                no++;
                i++;
            } while (!feof(fp));
            fclose(fp);
            printf("\t\t\t\t Pilih data yang akan diedit ( 1 -> %d ) atau ( 0 untuk kembali )\n", no - 1);
            range_int(&pilih, 0, no - 1, "\t\t\t\t >> ");
            if (pilih == 0)
            {
                menulistBarang("Diedit");
            }
            else if (pilih >= 1 && pilih <= no)
            {
                pilih -= 1;
                system("cls");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||               Data yang anda pilih               || \n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t || Nama Barang             : %s\n", y[pilih].nama);
                printf("\t\t\t\t || Harga per unit          : Rp.%s,-\n", y[pilih].harga);
                printf("\t\t\t\t || Sisa Stok               : %s\n", y[pilih].stok);
                printf("\t\t\t\t ======================================================\n\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||        Pilih opsi edit yang akan dipilih         ||\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||  [1]  || Edit Nama Barang                        ||\n");
                printf("\t\t\t\t ||       ||                                         ||\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||  [2]  || Edit Harga Barang                       ||\n");
                printf("\t\t\t\t ||       ||                                         ||\n");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||  [3]  || Edit Stok Barang                        ||\n");
                printf("\t\t\t\t ||       ||                                         ||\n");
                printf("\t\t\t\t ======================================================\n");
                range_int(&pilihEdit, 1, 3, "\t\t\t\t >> ");
                if (pilihEdit == 1)
                {
                    printf("\t\t\t\t =======================================================\n");
                    printf("\t\t\t\t ||    Masukkan nama baru dari data yang anda pilih   ||\n");
                    printf("\t\t\t\t =======================================================\n");
                    printf("\t\t\t\t >> ");
                    scanf("%[^\n]", namaBaru);
                    getchar();
                }
                else if (pilihEdit == 2)
                {
                    printf("\t\t\t\t =======================================================\n");
                    printf("\t\t\t\t ||   Masukkan harga baru dari data yang anda pilih   ||\n");
                    printf("\t\t\t\t =======================================================\n");
                    printf("\t\t\t\t >> Rp.");
                    scanf("%[^\n]", hargaBaru);
                    getchar();
                }
                else if (pilihEdit == 3)
                {
                    printf("\t\t\t\t =========================================================\n");
                    printf("\t\t\t\t || Masukkan jumlah stok baru dari data yang anda pilih ||\n");
                    printf("\t\t\t\t =========================================================\n");
                    printf("\t\t\t\t >> ");
                    scanf("%[^\n]", stokBaru);
                    getchar();
                }
                input_yakin(&yakin);
                if (yakin == 'Y')
                {
                    break;
                }
                else if (yakin == 'X')
                {
                    continue;
                }
            }
            else
            {
                pesanSalah();
            }
        }
        fp = fopen(namaFile, "r");
        fptemp = fopen("temp.txt", "w");
        do
        {
            read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", namaR, hargaR, stokR);
            if (read == 3)
            {
                if (strcmp(y[pilih].nama, namaR) == 0)
                {
                    if (pilihEdit == 1)
                    {
                        fprintf(fptemp, "%s,%s,%s\n", namaBaru, hargaR, stokR);
                    }
                    else if (pilihEdit == 2)
                    {
                        fprintf(fptemp, "%s,%s,%s\n", namaR, hargaBaru, stokR);
                    }
                    else if (pilihEdit == 3)
                    {
                        fprintf(fptemp, "%s,%s,%s\n", namaR, hargaR, stokBaru);
                    }
                }
                else
                {
                    fprintf(fptemp, "%s,%s,%s\n", namaR, hargaR, stokR);
                }
            }
        } while (!feof(fp));
        fclose(fp);
        fclose(fptemp);
        remove(namaFile);
        rename("temp.txt", namaFile);
        system("cls");
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t ||          Data telah berhasil diedit  !        ||\n");
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t           Tekan enter untuk melanjutkan...");
        getchar();
        cobalagi = cobaLagiG("Mengedit data");
    } while (cobalagi == 1);
    awalGudang();
}

void totalTransaksi()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 12/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menverifikasi pembelian bila sudah
        fix untuk melakukan transaksi pembelian, melakukan update ke stok barang yang tersedia,
        mencetak struk pembelian, dan mencatat data pembelian pada file riwayat pembelian
    */
    int bayar, kembalian, total = 0;
    int read;
    char namaPembeli[100];
    char buff[300];
    char nama[50], harga[20];
    char sisaChar[10];
    int sisaInt;
    int pajak;
    char waktu[50], waktuStruk[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(waktu, "%d,%02d,%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(waktuStruk, "(%02d:%02d:%02d) %d-%02d-%02d", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    system("cls");
    printf("\t\t\t\t =============================================\n");
    printf("\t\t\t\t ||          Masukkan Nama Pembeli          ||\n");
    printf("\t\t\t\t =============================================\n");
    printf("\t\t\t\t >> ");
    scanf("%[^\n]", namaPembeli);
    getchar();
    do
    {
        system("cls");
        printf("\t\t\t\t ============================================================\n");
        printf("\t\t\t\t ||                  Keterangan Transaksi                  ||\n");
        printf("\t\t\t\t ============================================================\n");
        printf("\t\t\t\t || Transaksi dengan nama : %s                               \n", namaPembeli);
        printf("\t\t\t\t || Waktu Transaksi       : %s                               \n", waktuStruk);
        printf("\t\t\t\t ============================================================\n");
        for (int i = 0; i <= n; i++)
        {
            printf("\t\t\t\t || Nama Barang : %s                          \n", *x[i].nama);
            printf("\t\t\t\t || Harga/unit  : Rp.%d,-                     \n", x[i].harga);
            printf("\t\t\t\t || Jumlah      : %d                          \n", x[i].jumlah);
            printf("\t\t\t\t || Total Harga : Rp.%d,-                     \n", x[i].totalHarga);
            printf("\t\t\t\t ============================================================\n");
            total += x[i].totalHarga;
        }
        pajak = total * PPN;
        printf("\t\t\t\t || Subtotal barang   : Rp.%d,- \n", total);
        printf("\t\t\t\t || Pajak PPN (11%%)   : Rp.%d,- \n", pajak);
        total += pajak;
        printf("\t\t\t\t ============================================================\n");
        printf("\t\t\t\t || Total Keseluruhan : Rp.%d,- \n", total);
        input_int(&bayar, "\t\t\t\t || Jumlah dibayar    : Rp.");
        if (bayar >= total)
        {
            kembalian = bayar - total;
            system("cls");
            printf("\t\t\t\t ======================================================\n");
            printf("\t\t\t\t ||          Terima Kasih Atas Pembelian Anda !      ||\n");
            printf("\t\t\t\t ======================================================\n");
            printf("\t\t\t\t || Kembalian anda : Rp.%d,- \n", kembalian);
            printf("\t\t\t\t ======================================================\n");
            printf("\t\t\t\t             Tekan enter untuk melanjutkan...");
            getchar();
            break;
        }
        else
        {
            printf(RED "\t\t\t\t Uang anda tidak mencukupi ! \n" COLOR_OFF);
        }
    } while (bayar < total);
    for (int i = 0; i <= n; i++)
    {
        fp = fopen(*x[i].namaFile, "r");
        fptemp = fopen("temp.txt", "w");
        do
        {
            read = fscanf(fp, "%50[^,],%15[^,],%15[^\n]\n", nama, harga, sisaChar);
            if (read == 3)
            {
                if (strcmp(*x[i].nama, nama) == 0)
                {
                    sisaInt = atoi(sisaChar);
                    sisaInt = sisaInt - x[i].jumlah;
                    sprintf(buff, "%s,%s,%d", nama, harga, sisaInt);
                    fprintf(fptemp, "%s\n", buff);
                }
                else
                {
                    fprintf(fptemp, "%s,%s,%s\n", nama, harga, sisaChar);
                }
            }
        } while (!feof(fp));
        fclose(fp);
        fclose(fptemp);
        remove(*x[i].namaFile);
        rename("temp.txt", *x[i].namaFile);
    }
    fp = fopen("strukpembayaran.txt", "w");
    fprintf(fp, "============================================================\n");
    fprintf(fp, "||                    Struk Pembayaran                    ||\n");
    fprintf(fp, "============================================================\n");
    fprintf(fp, "|| Transaksi dengan nama : %s                               \n", namaPembeli);
    fprintf(fp, "|| Waktu Transaksi       : %s                               \n", waktuStruk);
    fprintf(fp, "============================================================\n");
    for (int i = 0; i <= n; i++)
    {
        sprintf(buff, "|| Nama Barang : %s                          \n|| Harga/unit  : Rp.%d,-                     \n|| Jumlah      : %d                          \n|| Total Harga : Rp.%d,-                     \n============================================================\n", *x[i].nama, x[i].harga, x[i].jumlah, x[i].totalHarga);
        fprintf(fp, "%s", buff);
    }
    total = total - pajak;
    sprintf(buff, "|| Subtotal barang    : Rp.%d,- \n", total);
    fprintf(fp, "%s", buff);
    sprintf(buff, "|| Pajak PPN (11%%)    : Rp.%d,- \n", pajak);
    fprintf(fp, "%s", buff);
    total = total + pajak;
    sprintf(buff, "|| Total Keseluruhan  : Rp.%d,- \n", total);
    fprintf(fp, "%s", buff);
    fprintf(fp, "============================================================\n");
    sprintf(buff, "|| Dibayar sebesar   : Rp.%d,- \n", bayar);
    fprintf(fp, "%s", buff);
    sprintf(buff, "|| Kembalian anda    : Rp.%d,- \n", kembalian);
    fprintf(fp, "%s", buff);
    fprintf(fp, "============================================================\n");
    fclose(fp);
    system("cls");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||            Struk anda telah dicetak !            ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t             Tekan enter untuk melanjutkan...");
    getchar();
    fp = fopen("riwayatpembelian.txt", "a");
    for (int i = 0; i <= n; i++)
    {
        fprintf(fp, "%s,", waktu);
        sprintf(buff, "%s,%d,", *x[i].nama, x[i].jumlah);
        fprintf(fp, "%s", buff);
        sprintf(buff, "%d", x[i].totalHarga);
        fprintf(fp, "%s\n", buff);
    }
    fclose(fp);
    n = 0;
}

void tambahBarang(char *kategori, char *namaFile)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 13/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menambah data barang yang ada pada file
        dengan nama sesuai dengan parameter namaFile
        Parameter :
        namaFile (digunakan untuk menentukan file kategori barang mana yang akan ditambah datanya)
        kategori (digunakan untuk instruksi dalam mengkonfirmasi dat kategori mana yang akan ditambahkan)
    */
    system("cls");
    int cobalagi, pilih;
    char yakin;
    char namaG[100], hargaG[15], stokG[15];
    do
    {
        while (true)
        {
            system("cls");
            printf("\t\t\t\t ==============================================================\n");
            printf("\t\t\t\t ||    Konfirmasi menambah data barang ke kategori %s ?       \n", kategori);
            printf("\t\t\t\t ==============================================================\n");
            printf("\t\t\t\t  Pilih ( 1 -> Lanjut ) atau ( 0 -> kembali )\n");
            range_int(&pilih, 0, 1, "\t\t\t\t  >> ");
            if (pilih == 1)
            {
                system("cls");
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t ||      Masukkan nama barang yang akan ditambahkan     ||\n");
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> ");
                scanf("%[^\n]", namaG);
                getchar();
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t ||  Masukkan harga/unit dari barang dengan \n");
                printf("\t\t\t\t ||  Nama : %s \n", namaG);
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> Rp.");
                scanf("%[^\n]", hargaG);
                getchar();
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t || Masukkan banyak stok barang yang tersedia \n");
                printf("\t\t\t\t || dari barang dengan Nama : %s \n", namaG);
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> ");
                scanf("%[^\n]", stokG);
                getchar();
                system("cls");
                printf("\t\t\t\t ===================================================\n");
                printf("\t\t\t\t || Apakah anda yakin ingin menambahkan barang     \n");
                printf("\t\t\t\t || Dengan data dibawah pada Kategori %s ?         \n", kategori);
                printf("\t\t\t\t ===================================================\n");
                printf("\t\t\t\t || Nama        : %s                \n", namaG);
                printf("\t\t\t\t || Harga/unit  : Rp.%s,-                \n", hargaG);
                printf("\t\t\t\t || Stok        : %s unit           \n", stokG);
                printf("\t\t\t\t ===================================================\n");
                input_yakin(&yakin);
                if (yakin == 'Y')
                {
                    break;
                }
                else if (yakin == 'X')
                {
                    continue;
                }
            }
            else if (pilih == 0)
            {
                menulistBarang("Ditambah");
            }
        }
        system("cls");
        fp = fopen(namaFile, "a");
        fprintf(fp, "%s,%s,%s\n", namaG, hargaG, stokG);
        fclose(fp);
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t ||        Data telah berhasil ditambahkan !      ||\n");
        printf("\t\t\t\t ===================================================\n");
        printf("\t\t\t\t           Tekan enter untuk melanjutkan...");
        getchar();
        cobalagi = cobaLagiG("Menambahkan");
    } while (cobalagi == 1);
    awalGudang();
}

void stokHabis()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 12/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan teks bahwa
        stok dari barang yang akan dibeli telah habis
        fungsi ini dipanggil pada saat user ingin membeli
        barang yang stoknya habis/0
    */
    printf("\t\t\t\t ==========================================================\n");
    printf("\t\t\t\t ||  Jumlah stok barang yang anda akan beli sudah habis  ||\n");
    printf("\t\t\t\t ||               Silahkan ulang memilih !               ||\n");
    printf("\t\t\t\t ==========================================================\n");
    printf("\t\t\t\t              Tekan enter untuk melanjutkan...");
    getchar();
}

void pesanSalah()
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 12/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menampilkan teks bahwa
        ada yang salah pada input yang diberikan oleh user
    */
    printf(RED "\t\t\t\t =========================================================\n" COLOR_OFF);
    printf(RED "\t\t\t\t ||   Input Salah, Mohon Ikuti Petunjuk yang tersedia ! ||\n" COLOR_OFF);
    printf(RED "\t\t\t\t =========================================================\n" COLOR_OFF);
    printf("\t\t\t\t               Tekan enter untuk melanjutkan...");
    getchar();
}

int cobaLagiG(char *aksi)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 14/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menanyakan user apakah ingin
        melakukan sebuah aksi sesuai parameter atau tidak
        Parameter :
        aksi (digunakan untuk instruksi teks coba lagi yang ditanyakan)
        Return :
        1 -> untuk menyatakan bahwa user ingin mengulangi aksi
        0 -> untuk menyatakan bahwa user tidak ingin mengulangi aksi
    */
    system("cls");
    char yakin;
    printf("\t\t\t\t ========================================================\n");
    printf("\t\t\t\t ||    Apakah Anda Ingin %s Barang lagi ?  \n", aksi);
    printf("\t\t\t\t ========================================================\n");
    input_yakin(&yakin);
    if (yakin == 'Y')
    {
        return 1;
    }
    else if (yakin == 'X')
    {
        return 0;
    }
}

int konfirmasiBarang(char *nama, char *harga, char *stok)
{
    /*  Pembuat : Wahtu Astrawan
        Tanggal : 12/12/2022
        Revisi  : -
        Catatan :
        fungsi ini digunakan untuk menkonfirmasi barang yang akan dibeli
        dan menanyakan jumlah barang yang akan dibeli dan tidak boleh
        melebihi dari stok barang yg tersedia
        Parameter :
        nama (untuk menampilkan nama barang dari barang yg dipilih)
        harga (untuk menampilkan harga/unit barang dari barang yg dipilih)
        stok (untuk menampilkan banyak stok barang yg tersedia dari barang yg dipilih)
        Return :
        jumlah -> banyak barang yg akan dibeli oleh user
    */
    system("cls");
    int jumlah, status = 0, jumlahtemp = 0;
    int tersedia = atoi(stok);
    char yakin;
    printf("\t\t\t\t =======================================================\n");
    printf("\t\t\t\t ||               Konfirmasi Pembelian                || \n");
    printf("\t\t\t\t =======================================================\n");
    printf("\t\t\t\t || Nama Barang             : %s\n", nama);
    printf("\t\t\t\t || Harga per unit          : Rp.%s,-\n", harga);
    printf("\t\t\t\t || Sisa Stok               : %s\n", stok);
    printf("\t\t\t\t =======================================================\n");
    do
    {
        input_int(&jumlah, "\t\t\t\t  Jumlah yang akan dibeli \n\t\t\t\t  >> ");
        for (int i = 0; i < n; i++)
        {
            if (strcmp(*x[i].nama, nama) == 0)
            {
                jumlah += x[i].jumlah;
                jumlahtemp += x[i].jumlah;
                status++;
            }
        }
        if (status > 0)
        {
            printf("\t\t\t\t =============================================================\n");
            printf("\t\t\t\t ||   Peringatan bahwa sebelumnya anda telah mengkonfirmasi  \n");
            printf("\t\t\t\t ||        untuk membeli barang ini sebanyak %d unit         \n", jumlahtemp);
            printf("\t\t\t\t ||    dengan ini berarti anda membeli sebanyak %d unit      \n", jumlah);
            printf("\t\t\t\t =============================================================\n");
            printf("\t\t\t\t               Tekan enter untuk melanjutkan...");
            getchar();
        }
        if (jumlah < 1)
        {
            printf(RED "\t\t\t\t Jumlah yang akan dibeli tidak boleh kurang dari 1 ! \n" COLOR_OFF);
        }
        else if (jumlah > tersedia)
        {
            printf(RED "\t\t\t\t Jumlah yang akan dibeli melebihi stok yang tersedia ! \n" COLOR_OFF);
        }
        else
        {
            printf("\t\t\t\t ========================================\n");
            printf("\t\t\t\t ||         Apakah anda yakin ?        ||\n");
            printf("\t\t\t\t ========================================\n");
            input_yakin(&yakin);
            if (yakin == 'Y')
            {
                if (status > 0)
                {
                    return jumlah - jumlahtemp;
                }
                else
                {
                    return jumlah;
                }
            }
            else if (yakin = 'X')
            {
                jumlah = 0;
                return jumlah;
            }
        }

    } while (jumlah < 1 || jumlah > tersedia);
}

void daftarBarang() // Fungsi Untuk menampilkan header dari Daftar list barang
{
    printf("\t\t\t\t ==========================================================\n");
    printf("\t\t\t\t ||            List Nama, Harga, dan Stok Barang         ||\n");
    printf("\t\t\t\t ==========================================================\n");
    printf("\t\t\t\t ||  Pilihan    ||              NAMA BARANG              ||\n");
    printf("\t\t\t\t ==========================================================\n");
}

void input_int(int *var, char *intruksi) // Fungsi untuk input integer
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
        printf(RED "\t\t\t\tInput salah! Mohon Masukan Angka!\n" COLOR_OFF);
    }
}

void range_int(int *var, int range1, int range2, char *intruksi) // Fungsi untuk integer dengan range (jarak) nilai
{
    while (1)
    {
        input_int(var, intruksi);
        fflush(stdin);
        if (*var >= range1 && *var <= range2)
            break;
        printf(RED "\t\t\t\tMohon masukkan angka sesuai dengan petunjuk ! \n" COLOR_OFF);
    }
}

void input_yakin(char *var) // Validasi Memasukkan ya(Y) atau tidak(X)
{
    char input[1024];
    while (true)
    {
        printf("\t\t\t\t  Masukan y untuk iya atau x untuk tidak \n");
        printf("\t\t\t\t  >> ");
        scanf("%[^\n]", input);
        getchar();
        *var = toupper(*input);
        if (strlen(input) <= 1)
        {
            if (*var == 88 || *var == 89)
            {
                break;
            }
        }
        printf(RED "\t\t\t\tMaaf input salah, Mohon ikuti petunjuk ! \n" COLOR_OFF);
    }
}
