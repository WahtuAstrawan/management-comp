#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Define warna
#define BOLD "\e[1m"
#define COLOR_OFF "\e[m"
#define RED "\033[31m"
#define GREEN "\e[32m\e[1m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BLACK_GREEN_ITALIC "\033[3;30;42m"
#define BLACK_RED_STRIKE "\033[9;30;41m"
#define RED_BOLD "\e[1;5;31m"

// Pendeklarasian seluruh fungsi
void intro(), awalCashier(), menu(),
    loading(), range_int(), input_int();

// Pendeklarasian Variabel
FILE *fp, *fptemp;
typedef struct Barang
{
    char *nama[100];
    char *harga[15];
    char *stok[15];
} prosesor[50];

int n = 0;

typedef struct Beli
{
    char *nama[100];
    int harga;
    int jumlah;
    int totalHarga;
} transaksi[50];

transaksi x;

int main()
{
    system("color f0");
    intro();
    return 0;
}

void intro()
{
    system("clear");
    printf(BLACK_RED_STRIKE "\t\t\t\t                                                      \n" COLOR_OFF);
    printf(BLACK_RED_STRIKE "\t\t\t\t " COLOR_OFF GREEN "                                                    " COLOR_OFF BLACK_RED_STRIKE " \n" COLOR_OFF);
    printf(BLACK_GREEN_ITALIC "\t\t\t\t                                                      \n" COLOR_OFF);
    printf(BLACK_GREEN_ITALIC "\t\t\t\t                 LIANWA MANAGEMENT                    \n" COLOR_OFF);
    printf(BLACK_GREEN_ITALIC "\t\t\t\t                                                      \n" COLOR_OFF);
    printf(BLACK_RED_STRIKE "\t\t\t\t " COLOR_OFF GREEN "                                                    " COLOR_OFF BLACK_RED_STRIKE " \n" COLOR_OFF);
    printf(BLACK_RED_STRIKE "\t\t\t\t                                                      \n" COLOR_OFF);
    printf("\n\t\t\t\t          Tekan enter untuk melanjutkan....");
    getchar();
    awalCashier();
    // Menuju Menu login atau registrasi
}

void awalCashier()
{
    // Setelah login sebagai cashier
    system("clear");
    int pilih;
    char yakin;
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t |                   LIANWA CASHIER                   |\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |  Pilihan |                MAIN MENU                |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [1]    |  Transaksi                              |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [2]    |  Logout                                 |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    range_int(&pilih, 1, 2, "\t\t\t\t  Pilihan kamu (1/2) : ");
    if (pilih == 1)
    {
        menulistBarang();
    }
    else
    {
        system("clear");
        printf("\t\t\t\t +----------------------------------------------------+\n");
        printf("\t\t\t\t |          Apakah anda yakin ingin logout ?          |\n");
        printf("\t\t\t\t +----------------------------------------------------+\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            // ke menu login
            intro();
        }
        else if (yakin == 'X')
        {
            awalCashier();
        }
    }
}

void awalGudang()
{
    // Setelah login sebagai gudang
    system("clear");
    int pilih;
    char yakin;
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t |                  LIANWA WAREHOUSE                  |\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |  Pilihan |                MAIN MENU                |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [1]    |  Tambah Data Barang                     |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [2]    |  Edit Data Barang                       |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [3]    |  Hapus Data Barang                      |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t |   [4]    |  Logout                                 |\n");
    printf("\t\t\t\t |          |                                         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    range_int(&pilih, 1, 4, "\t\t\t\t  Pilihan kamu (1/2/3/4) : ");
    if (pilih == 1)
    {
        // Ke fungsi Tambah data barang
    }
    else if (pilih == 2)
    {
        // Ke fungsi Edit data barang
    }
    else if (pilih == 3)
    {
        // Ke fungsi Hapus data barang
    }
    else
    {
        system("clear");
        printf("\t\t\t\t +----------------------------------------------------+\n");
        printf("\t\t\t\t |          Apakah anda yakin ingin logout ?          |\n");
        printf("\t\t\t\t +----------------------------------------------------+\n");
        input_yakin(&yakin);
        if (yakin == 'Y')
        {
            // Ke menu login
            intro();
        }
        else if (yakin == 'X')
        {
            awalGudang();
        }
    }
}

void menulistBarang()
{
    system("clear");
    int pilih;
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t |                  LIST JENIS BARANG                 |\n");
    printf("\t\t\t\t |                                                    |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |  Pilihan |              NAMA KOMPONEN              |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [1]    | Processor                               |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [2]    | GPU                                     |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [3]    | RAM                                     |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [4]    | Keyboard                                |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [5]    | Mouse                                   |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [6]    | Monitor                                 |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |   [7]    | Headset                                 |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    range_int(&pilih, 1, 7, "\t\t\t\t  Pilihan kamu (1 -> 7) : ");
    if (pilih == 1)
    {
        processor();
    }
    else if (pilih == 2)
    {
        // Ke transaksi GPU
    }
    else if (pilih == 3)
    {
        // Ke transaksi RAM
    }
    else if (pilih == 4)
    {
        // Ke transaksi Keyboard
    }
    else if (pilih == 5)
    {
        // Ke transaksi Mouse
    }
    else if (pilih == 6)
    {
        // Ke transaksi Monitor
    }
    else if (pilih == 7)
    {
        // Ke transaksi Headset
    }
    else
    {
        pesanSalah();
        menulistBarang();
    }
}

void processor()
{
    system("clear");
    prosesor a;
    int pilih, jumlah;
    char yakin;
    int i = 0, read, no = 1;
    fp = fopen("prosesor.txt", "r");
    daftarBarang();
    do
    {
        read = fscanf(fp, "%50[^,],%15[^,],%15[^\n]\n", a[i].nama, a[i].harga, a[i].stok);
        printf("\t\t\t\t |   [%d]    | %s                                      \n", no, a[i].nama);
        printf("\t\t\t\t |          | Harga        : Rp.%s,-                   \n", a[i].harga);
        printf("\t\t\t\t |          | Jumlah Stok  : %s                        \n", a[i].stok);
        printf("\t\t\t\t +----------+-----------------------------------------+\n");
        no++;
        i++;
    } while (!feof(fp));
    fclose(fp);
    // char listBarang[i][100];
    // int harga[i];
    // int stok[i];
    // for (int n = 0; n < i; n++)
    // {
    //     *listBarang[n] = a[n].nama;
    //     harga[n] = atoi(a[n].harga);
    //     stok[n] = atoi(a[n].stok);
    // }
    do
    {
        printf("\t\t\t\t Pilihan anda (1 -> %d ) : ", no - 1);
        range_int(&pilih, 1, no - 1, "");
        if (pilih >= 1 && pilih <= no)
        {
            pilih -= 1;
            jumlah = konfirmasiBarang(a[pilih].nama, a[pilih].harga, a[pilih].stok);
            if (jumlah == 0)
            {
                processor();
            }
            else
            {
                *x[n].nama = a[pilih].nama;
                x[n].harga = atoi(a[pilih].harga);
                x[n].jumlah = jumlah;
                x[n].totalHarga = (x[n].harga * x[n].jumlah);
                break;
            }
        }
        else
        {
            pesanSalah();
        }
    } while (pilih < 1 || pilih > no);
    printf("\t\t\t\t +------------------------------------------------------+\n");
    printf("\t\t\t\t |        Apakah Anda Ingin membeli barang lagi ?       |\n");
    printf("\t\t\t\t +------------------------------------------------------+\n");
    input_yakin(&yakin);
    if (yakin == 'Y')
    {
        // Ke menu lagi
    }
    else if (yakin == 'X')
    {
        totalTransaksi(x[n].nama, x[n].harga, x[n].jumlah, x[n].totalHarga);
        n++;
    }
}

void totalTransaksi(char *nama, int harga, int jumlah, int total)
{
    int bayar, kembalian;
    do
    {
        system("clear");
        printf("\t\t\t\t +------------------------------------------------------+\n");
        printf("\t\t\t\t | Barang yang anda beli : %s\n", nama);
        printf("\t\t\t\t | Harga                 : Rp.%d,-\n", harga);
        printf("\t\t\t\t | Jumlah                : %d unit\n", jumlah);
        printf("\t\t\t\t | Total Harga           : Rp.%d,-\n", total);
        printf("\t\t\t\t +------------------------------------------------------+\n");
        printf("\t\t\t\t Total Bayar (Rp) : ");
        bayar = validasiInteger();
        if (bayar < total)
        {
            printf(RED "\t\t\t\t Uang anda tidak mencukupi ! " COLOR_OFF);
        }
        else
        {
            kembalian = bayar - total;
            printf(BOLD "\t\t\t\t Terima Kasih Atas Pembelian Anda !" COLOR_OFF);
            printf(BOLD "\t\t\t\t Kembalian Anda : Rp.%d,- " COLOR_OFF, kembalian);
        }
    } while (bayar < total);
}

void pesanSalah()
{
    printf("\t\t\t\t +------------------------------------------------------+\n");
    printf("\t\t\t\t |   Input Salah, Mohon Ikuti Petunjuk yang tersedia !  |\n");
    printf("\t\t\t\t +------------------------------------------------------+\n");
}

int konfirmasiBarang(char *nama, char *harga, char *stok)
{
    system("clear");
    int jumlah;
    char yakin;
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t |                Konfirmasi Pembelian                |\n");
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t | Nama Barang             : %s\n", nama);
    printf("\t\t\t\t | Harga per unit          : %s\n", harga);
    printf("\t\t\t\t | Sisa Stok               : %s\n", stok);
    printf("\t\t\t\t +----------------------------------------------------+\n");
    do
    {
        printf("\t\t\t\t  Jumlah yang akan dibeli : ");
        jumlah = validasiInteger();
        fflush(stdin);
        if (jumlah < 1)
        {
            printf(RED "\t\t\t\t Jumlah yang akan dibeli tidak boleh kurang dari 1 !" COLOR_OFF);
        }
        else
        {
            if (jumlah > stok)
            {
                printf(RED "\t\t\t\t Jumlah yang akan dibeli melebihi stok yang tersedia !" COLOR_OFF);
            }
            else
            {
                return jumlah;
                // input_yakin(&yakin);
                // if (yakin == 'Y')
                // {
                //     return jumlah;
                // }
                // else if (yakin = 'X')
                // {
                //     jumlah = 0;
                //     return jumlah;
                // }
            }
        }
    } while (jumlah < 1 || jumlah > stok);
}

void daftarBarang()
{
    printf("\t\t\t\t +----------------------------------------------------+\n");
    printf("\t\t\t\t |          List Nama Barang, Harga, dan Stok         |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
    printf("\t\t\t\t |  Pilihan |               NAMA BARANG               |\n");
    printf("\t\t\t\t +----------+-----------------------------------------+\n");
}

void input_int(int *var, char *intruksi)
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
        printf("\033[0;31m\t\t\t\tInput salah! Mohon Masukan Angka!\033[0m\n");
    }
}

void range_int(int *var, int range1, int range2, char *intruksi)
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

int validasiInteger()
{
    while (true)
    {
        char input[100], notValid;
        int valid;
        scanf("%[^\n]", input);
        fflush(stdin);
        if (sscanf(input, "%d%c", &valid, &notValid) == 1)
        {
            return valid;
            break;
        }
        else
        {
            printf(RED "\n\t\t\t\tMaaf input salah, Mohon masukkan angka ! \n" COLOR_OFF);
        }
    }
}

void input_yakin(char *var)
{
    while (true)
    {
        printf("\t\t\t\t Masukan x untuk tidak dan y untuk iya\n");
        printf("\t\t\t\t Masukan (x/y) : ");
        scanf("%c", var);
        getchar();
        *var = toupper(*var);
        if (*var == 88 || *var == 89)
        {
            break;
        }
        else
        {
            printf("\t\t\t\t Masukan x untuk tidak dan y untuk iya\n");
        }
    }
}
