#include <stdio.h> //(1240505901 UMUT TÜTER)
#include <stdlib.h>
#include <time.h> 
#include <ctype.h> 
int saglik = 100;
int enerji = 100;
int yemek_sayisi = 5;
int siginak_durumu = 0; 
char komut;

void durumu_goster() {
    printf(" Mevcut Durum:\n");
    printf("   Saglik: %d/100 | Enerji: %d/100 | Yemek: %d\n", saglik, enerji, yemek_sayisi);
    printf("   Siginak: %s\n", siginak_durumu ? "BULUNDU" : "Yok");
    printf("-------------------------------------------------\n");
}

void durumu_kontrol_et() {
    if (enerji > 100) enerji = 100;
    if (saglik > 100) saglik = 100;
    if (enerji < 0) enerji = 0;
    if (saglik < 0) saglik = 0;
}

int main() {
    int i; 
    
    srand(time(NULL));

    printf("- Hayatta Kalma Simulatoru Basladi  -\n");
    printf("Komutlar: A(Avlan), S(Siginak), R(Dinlen), E(Envanter), F(Tehlike), P(Sifre), X(Cikis)\n");

    do {
        durumu_kontrol_et();
        durumu_goster();

        if (saglik <= 0) {
            printf("\n Hayatta kalamadin. Oyun bitti.\n");
            break;
        }

        printf("Komut giriniz: ");
        
        if (scanf(" %c", &komut) != 1) {
            break;
        }
        
        komut = toupper(komut); 
        
        switch (komut) {
            case 'A': 
                printf("\n Avlaniyorsun...\n");
                
                if (enerji < 15) {
                    printf("Cok yorgunsun, avlanmaya yetecek enerjin yok (min 15 enerji gerekli).\n");
                    break;
                }
                enerji -= 15; 
                
                int sans = rand() % 100;
                
                if (sans < 60 && siginak_durumu == 0) { 
                    int kazanilan_yemek = 1 + rand() % 3;
                    yemek_sayisi += kazanilan_yemek;
                    printf("?? Basarili av! %d yemek kazandin.\n", kazanilan_yemek);
                } else if (sans < 80 || enerji <= 20) { 
                    int kayip = 5 + rand() % 10;
                    saglik -= kayip;
                    printf("?? Av sirasinda yaralandin! %d saglik kaybettin.\n", kayip);
                } else {
                    printf("Av basarili olmadi, hicbir sey bulamadin.\n");
                }
                break;

            case 'S': 
                printf("\n Siginak ariyorsun...\n");
                
               
                if (siginak_durumu == 1) {
                    printf("Zaten guvenli bir siginagin var.\n");
                } else {
                    if (rand() % 100 < 35) {
                        siginak_durumu = 1;
                        printf(" Mukemmel! Bir siginak buldun ve guvendesin.\n");
                    } else {
                        printf(" Siginak bulma cabasi sonucsuz kaldi.\n");
                    }
                }
                break;

            case 'E': 
                printf("\n Envanter: %d Yemek.\n", yemek_sayisi);
                break;

            case 'R': 
                printf("\n Dinleniyorsun...\n");
                
                enerji += 35; 
                
                if (siginak_durumu == 1) {
                    saglik += 15;
                    printf("Guvenli siginakta oldugun icin daha iyi dinlendin ve %d saglik kazandin.\n", 15);
                } else {
                    saglik += 5;
                    printf("Acýkta dinleniyorsun, dikkatli ol. %d saglik kazandin.\n", 5);
                }
                
                break;
                
            case 'F': 
                printf("\n BOLGEDE TEHLIKE SERÝSÝ BASLADI! ??\n");
                
               
                int dalga_sayisi = 3;
                
               
                for (i = 1; i <= dalga_sayisi; i++) { 
                    if (saglik <= 0) break; 
                    
                    printf("--- Dalga %d ---\n", i);
                    int tehlike = rand() % 100;
                    
                    if (tehlike < 50 && siginak_durumu == 0) {
                        int kayip = 10 + rand() % 5;
                        saglik -= kayip;
                        printf(" Saldiriya ugradin! %d saglik kaybettin.\n", kayip);
                    } else if (tehlike < 70) {
                        enerji -= 10;
                        printf(" Yorucu bir kacis. 10 enerji kaybettin.\n");
                    } else {
                        printf(" Tehlikeyi basariyla atlattin.\n");
                    }
                    durumu_kontrol_et();
                }
                printf("Tehlike serisi sona erdi.\n");
                break;
                
            case 'P': { 
                printf("\n Kilitli bir engelle karsýlastin. Sifreyi bulmalisin.\n");
                
                
                char gizli_sifre = 'C'; 
                char girilen_sifre;
                int deneme_hakki = 3;

                
                do {
                    printf("Sifreyi gir (Tek karakter, örn: A, B, C): ");
                    if (scanf(" %c", &girilen_sifre) != 1) {
                        break; 
                    }
                    girilen_sifre = toupper(girilen_sifre);
                    deneme_hakki--;
                    
                    if (girilen_sifre == gizli_sifre) {
                        printf(" Sifre dogru! Engeli astin.\n");
                        break;
                    } else {
                        printf(" Yanlis sifre. Kalan hak: %d\n", deneme_hakki);
                    }
                    
                    if (deneme_hakki == 0) {
                        printf(" Tum haklar tukendi. 5 Saglik Kaybi cezasi aldin.\n");
                        saglik -= 5;
                        break;
                    }

                } while (girilen_sifre != gizli_sifre);
                break;
            }

            case 'X': 
                printf("\n Simulatorden cikiliyor...\n");
                break;

            default:
                printf("\n Gecersiz komut '%c'. Lutfen gecerli bir komut giriniz.\n", komut);
                break;
        }

    } while (komut != 'X' && saglik > 0);

    
    printf("\n Simulator Bitti. Son Durum: Saglik %d, Enerji %d \n", saglik, enerji);
    return 0;
}
