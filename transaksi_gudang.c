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
    input_yakin(char *var);

int cobaLagiG(char *aksi), konfirmasiBarang(char *nama, char *harga, char *stok);

// Pendeklarasian Variabel dan Struct Global
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
    system("clear");
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
    awalGudang();
    // Menuju Menu login atau registrasi
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
    system("clear");
    jenisLogin = 11;
    int pilih;
    char yakin;
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||...............CASHIER TRANSACTIONS...............||\n");
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
        system("clear");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin logout ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
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
    else
    {
        system("clear");
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
    system("clear");
    jenisLogin = 22;
    n = 0;
    int pilih;
    char yakin;
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||                                                  ||\n");
    printf("\t\t\t\t ||.................WAREHOUSE ACTIVITY...............||\n");
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
        system("clear");
        printf("\t\t\t\t ======================================================\n");
        printf("\t\t\t\t ||          Apakah anda yakin ingin logout ?        ||\n");
        printf("\t\t\t\t ======================================================\n");
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
    else
    {
        system("clear");
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
    system("clear");
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
            system("clear");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", a[i].nama, a[i].harga, a[i].stok);
                printf("\t\t\t\t ||             || %s                                      \n", a[i].nama);
                printf("\t\t\t\t ||     [%d]     || Harga/unit  : Rp.%s,-                  \n", no, a[i].harga);
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
        system("clear");
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
            system("clear");
            int i = 0, no = 1;
            fp = fopen(namaFile, "r");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", z[i].nama, z[i].harga, z[i].stok);
                printf("\t\t\t\t ||             || %s                                      \n", z[i].nama);
                printf("\t\t\t\t ||   [%d]       || Harga/unit   : Rp.%s,-                  \n", no, z[i].harga);
                printf("\t\t\t\t ||             || Jumlah Stok  : %s                        \n", z[i].stok);
                printf("\t\t\t\t ==========================================================\n");
                no++;
                i++;
            } while (!feof(fp));
            fclose(fp);
            printf("\t\t\t\t Pilih data yang akan dihapus ( 1 -> %d ) atau ( 0 untuk kembali ) \n\t\t\t\t >> ", no - 1);
            range_int(&pilih, 0, no - 1, "");
            if (pilih == 0)
            {
                menulistBarang("Dihapus");
            }
            else if (pilih >= 1 && pilih <= no)
            {
                pilih -= 1;
                system("clear");
                printf("\t\t\t\t ======================================================\n");
                printf("\t\t\t\t ||               Data yang anda pilih               || \n");
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
        system("clear");
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
            system("clear");
            int i = 0, no = 1;
            fp = fopen(namaFile, "r");
            daftarBarang();
            do
            {
                read = fscanf(fp, "%100[^,],%15[^,],%15[^\n]\n", y[i].nama, y[i].harga, y[i].stok);
                printf("\t\t\t\t ||             || %s                                       \n", y[i].nama);
                printf("\t\t\t\t ||   [%d]       || Harga/unit   : Rp.%s,-                  \n", no, y[i].harga);
                printf("\t\t\t\t ||             || Jumlah Stok  : %s                        \n", y[i].stok);
                printf("\t\t\t\t ==========================================================\n");
                no++;
                i++;
            } while (!feof(fp));
            fclose(fp);
            printf("\t\t\t\t Pilih data yang akan diedit ( 1 -> %d ) atau ( 0 untuk kembali ) : ", no - 1);
            range_int(&pilih, 0, no - 1, "");
            if (pilih == 0)
            {
                menulistBarang("Diedit");
            }
            else if (pilih >= 1 && pilih <= no)
            {
                pilih -= 1;
                system("clear");
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
        system("clear");
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
    system("clear");
    printf("\t\t\t\t =============================================\n");
    printf("\t\t\t\t ||          Masukkan Nama Pembeli          ||\n");
    printf("\t\t\t\t =============================================\n");
    printf("\t\t\t\t >> ");
    scanf("%[^\n]", namaPembeli);
    getchar();
    do
    {
        system("clear");
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
            system("clear");
            printf("\t\t\t\t ======================================================\n");
            printf("\t\t\t\t ||          Terima Kasih Atas Pembelian Anda !      ||\n");
            printf("\t\t\t\t ======================================================\n");
            printf("\t\t\t\t   Kembalian anda : Rp.%d,- \n", kembalian);
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
    sprintf(buff, "|| Total Keseluruhan : Rp.%d,- \n", total);
    fprintf(fp, "%s", buff);
    fprintf(fp, "============================================================\n");
    sprintf(buff, "|| Dibayar sebesar   : Rp.%d,- \n", bayar);
    fprintf(fp, "%s", buff);
    sprintf(buff, "|| Kembalian anda    : Rp.%d,- \n", kembalian);
    fprintf(fp, "%s", buff);
    fprintf(fp, "============================================================\n");
    fclose(fp);
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t ||            Struk anda telah dicetak !            ||\n");
    printf("\t\t\t\t ======================================================\n");
    printf("\t\t\t\t             Tekan enter untuk melanjutkan...");
    getchar();
    fp = fopen("riwayatpembelian.txt", "a");
    fprintf(fp, "%s,", waktu);
    for (int i = 0; i <= n; i++)
    {
        sprintf(buff, "%s,%d,", *x[i].nama, x[i].jumlah);
        fprintf(fp, "%s", buff);
    }
    sprintf(buff, "%d", total - pajak);
    fprintf(fp, "%s\n", buff);
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
    system("clear");
    int cobalagi, pilih;
    char yakin;
    char namaG[100], hargaG[15], stokG[15];
    do
    {
        system("clear");
        printf("\t\t\t\t ==============================================================\n");
        printf("\t\t\t\t ||    Konfirmasi menambah data barang ke kategori %s ?       \n", kategori);
        printf("\t\t\t\t ==============================================================\n");
        printf("\t\t\t\t  Pilih ( 1 -> Lanjut ) atau ( 0 -> kembali )\n");
        range_int(&pilih, 0, 1, "\t\t\t\t  >> ");
        if (pilih == 1)
        {
            while (true)
            {
                system("clear");
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t ||      Masukkan nama barang yang akan ditambahkan     ||\n");
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> ");
                scanf("%[^\n]", namaG);
                getchar();
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t ||  Masukkan harga/unit dari barang dengan Nama : %s \n", namaG);
                printf("\t\t\t\t ||                yang akan ditambahkan  \n");
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> Rp.");
                scanf("%[^\n]", hargaG);
                getchar();
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t ||      Masukkan banyak stok barang yang tersedia \n");
                printf("\t\t\t\t ||              dari barang dengan Nama : %s \n", namaG);
                printf("\t\t\t\t =========================================================\n");
                printf("\t\t\t\t  >> ");
                scanf("%[^\n]", stokG);
                getchar();
                system("clear");
                printf("\t\t\t\t ===================================================\n");
                printf("\t\t\t\t || Apakah anda yakin ingin menambahkan barang     \n");
                printf("\t\t\t\t || Dengan data dibawah pada Kategori %s ?         \n", kategori);
                printf("\t\t\t\t ===================================================\n");
                printf("\t\t\t\t || Nama        : %s                \n", namaG);
                printf("\t\t\t\t || Harga/unit  : %s                \n", hargaG);
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
        }
        else if (pilih == 0)
        {
            menulistBarang("Ditambah");
        }
        system("clear");
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
    system("clear");
    int jumlah, status, jumlahtemp = 0;
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
                return jumlah;
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
