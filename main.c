#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 500

// ALFA-KOD Şifreleme Sistemi - C Dili Uygulaması
// ÇARPAN = 3, ANAHTAR = 17, TERS ÇARPAN = 10, mod 29
// (A=1, B=2, ..., Z=26, Harf Yok=0)

// Harf -> Kod dönüşümü
int get_code(char c) {
    if (c == ' ') return 0;
    c = toupper(c);                    // Küçük harf girilse bile büyük yap
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 1;            // A=1, B=2, ..., M=13, Z=26
    }
    return -1; // Geçersiz karakter
}

// Kod -> Harf dönüşümü
char get_char(int code) {
    if (code == 0) return ' ';
    if (code >= 1 && code <= 26) {
        return 'A' + code - 1;
    }
    return '?';
}

// Negatif mod için yardımcı fonksiyon
long long positive_mod(long long x, long long m) {
    return (x % m + m) % m;
}

int main() {
    int secim, anahtar = 17;
    char metin[MAX];
    char sifreli_girdi[MAX];

    printf("========================================\n");
    printf("   ALFA-KOD - Kişisel Şifreleme Sistemim\n");
    printf("   (Matematik Projesi - C Dili Uygulaması)\n");
    printf("========================================\n\n");

    while (1) {
        printf("\n1 - Metin Şifrele\n");
        printf("2 - Şifreli Metni Çöz\n");
        printf("3 - Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &secim);
        getchar(); // newline temizle

        if (secim == 3) {
            printf("\nALFA-KOD kapatılıyor...\n");
            break;
        }

        if (secim == 1) {
            // ŞİFRELEME
            printf("\nŞifrelenecek metni girin (BÜYÜK harflerle): ");
            fgets(metin, MAX, stdin);
            metin[strcspn(metin, "\n")] = '\0';

            printf("\nŞifrelenmiş metin: ");
            int i = 0;
            int ilk = 1;
            while (metin[i] != '\0') {
                int kod = get_code(metin[i]);
                if (kod != -1) {
                    if (!ilk) printf("-");
                    long long sifreli = positive_mod((long long)kod * 3 + anahtar, 29);
                    printf("%lld", sifreli);
                    ilk = 0;
                }
                i++;
            }
            printf("\n\n");
            printf("Örnek (projenizdeki gibi): MERHABA → 27-3-13-12-20-23-20\n");

        } else if (secim == 2) {
            // ÇÖZME
            printf("\nÇözülecek şifreli metni girin (sayılar - ile ayrılmış): ");
            fgets(sifreli_girdi, MAX, stdin);
            sifreli_girdi[strcspn(sifreli_girdi, "\n")] = '\0';

            printf("\nÇözülmüş orijinal metin: ");

            char *token = strtok(sifreli_girdi, "-");
            while (token != NULL) {
                int num = atoi(token);
                long long temp = (long long)num - anahtar;
                long long cozulen_kod = positive_mod(temp * 10, 29);
                printf("%c", get_char((int)cozulen_kod));
                token = strtok(NULL, "-");
            }
            printf("\n\n");
            printf("Örnek (projenizdeki gibi): 27-3-13-12-20-23-20 → MERHABA\n");

        } else {
            printf("Geçersiz seçim!\n");
        }
    }

    return 0;
}