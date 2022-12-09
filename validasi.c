#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define RED "\033[31m"
#define COLOR_OFF "\e[m"

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
        printf("\033[0;31m\t\t\t Input salah! Mohon Masukan Angka!\n\033[0m");
    }
}
void range_int(int *var, int range1, int range2, char *intruksi, char *salah) // membatasi input
{
    while (1)
    {
        input_int(var, intruksi);
        fflush(stdin);
        if (*var >= range1 && *var <= range2)
            break;
        printf("\033[0;31m");
        printf("%s", salah);
        printf("\033[0m");
    }
}
void input_pilihan(char *var)
{
    while (1)
    {
        printf("Masukan Pilihan : ");
        fflush(stdin);
        scanf("%c", var);
        *var = toupper(*var);
        if (*var >= 65 && *var <= 69)
        {
            break;
        }

        printf("\t\tMasukan Pilihan Yang Tersedia\n");
    }
}
void input_username(char *var)
{
    char buff[1024];
    char cek;
    int i = 0;
    while (1)
    {
        ulang:
        printf("Masukan username : ");
        fflush(stdin);

        if (fgets(buff, sizeof(buff), stdin) != NULL)
        {

            if (sscanf(buff, "%s %c", var, &cek) == 1)
            {
                while (var[i])
                {
                    if (!isalpha(var[i]))
                    {
                        printf("\t\tInput salah\n\t\tMohon gunakan huruf saja\n");
                        goto ulang;
                    }

                    i++;
                }

                break;
            }
        }

        printf("\t\tUsername Tidak Boleh ada spasi\n");
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
            printf(RED "\nMaaf input salah, Mohon masukkan angka ! \n" COLOR_OFF);
        }
    }
}

//main cuma ngetest wkwk
int main()
{
    char h[400];
    input_username(h);
    printf("%s", h);
    return 0;
}
