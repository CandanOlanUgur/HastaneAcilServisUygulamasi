#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct gunluk {
    char message[300];
    struct gunluk *next;
} gunluk;

typedef struct hasta {
    int hastaNo;
    char hasta_adSoyad[30];
    char tc[12]; // 11-digit TC + null character
    char sikayet[20];
    int oncelik;
    int yas;
    struct hasta *next;
} hasta;


long a = 202503;

gunluk *gunlukEkle(hasta *head, gunluk *head1) {

    gunluk *yeni_gunluk = (gunluk *)malloc(sizeof(gunluk));
    char new_message[300];

    sprintf(new_message,"MSH|^~\\&|HOSPITAL|EMERGENCY|HASTAKABUL|%ld||ADT^A01|123456|P|2.3\n"
                                  "EVN|A01|202503011200\n"
                                  "PID|1||123456^^^HOSPITAL|%s|%s|19850101|M|||%d|\n"
                                  "PV1|1|E|ER^01^1|R|||12345|||||||TR||||ONCELIK>>%d||ER\n",a,head -> tc,head -> hasta_adSoyad,head -> hastaNo,head -> oncelik);

    strcpy(yeni_gunluk->message,new_message);
    yeni_gunluk->next = head1;
    head1 = yeni_gunluk;

    printf("------------------------\n");
    printf("Gunluk Guncellendi\n");
    printf("------------------------\n");

    return head1;
}



hasta *yeniHastaKayit(hasta *head, int hastaNo) {
    hasta *yeni_hasta = (hasta *)malloc(sizeof(hasta));


    if (yeni_hasta == NULL) {
        printf("Bellek tahsis hatası!\n");
        return head;
    }


    yeni_hasta->hastaNo = hastaNo;

    printf("Hasta Ad Soyad: ");
    fgets(yeni_hasta->hasta_adSoyad, sizeof(yeni_hasta->hasta_adSoyad), stdin);
    yeni_hasta->hasta_adSoyad[strcspn(yeni_hasta->hasta_adSoyad, "\n")] = 0;  // "/n" hatasını giderme


    printf("Hasta TC: ");
    fgets(yeni_hasta->tc, sizeof(yeni_hasta->tc), stdin);
    yeni_hasta->tc[strcspn(yeni_hasta->tc, "\n")] = 0;  // "/n" hatasını giderme
    while (getchar() != '\n'); // bosluk hatasını giderme

    printf("Sikayet: ");
    fgets(yeni_hasta->sikayet, sizeof(yeni_hasta->sikayet), stdin);
    yeni_hasta->sikayet[strcspn(yeni_hasta->sikayet, "\n")] = 0; // "/n" hatasını giderme

    printf("Oncelik (1-Kirmizi,2-Sari,3-Yesil): ");
    scanf("%d", &yeni_hasta->oncelik);
    while (getchar() != '\n');  // bosluk hatasını giderme

    printf("Yas: ");
    scanf("%d", &yeni_hasta->yas);
    while (getchar() != '\n');  // bosluk hatasını giderme



    if (head == NULL) {
        head = yeni_hasta;
        head -> next = NULL;
        printf("Hasta kaydedildi... \n");
    }

    else {
        yeni_hasta->next = head;
        head = yeni_hasta;
        printf("Hasta kaydedildi... \n");
    }

    return head;
}

hasta *hastaTaburcuEt(hasta *head) {

    bool sonuc = false;
    if (head == NULL) {
        printf("Hasta Yok...\n");

        return head;
        sonuc = true;
    }

    else {
        int taburcu_hastaNo;

        printf("Taburcu edilecek hastanin hasta numarasi: ");
        scanf("%d", &taburcu_hastaNo);


        if (head->hastaNo == taburcu_hastaNo && head -> next == NULL) {
            free(head);
            head = NULL;
            printf("Hasta taburcu edildi...\n");
            sonuc = true;
        }

        else if (head->hastaNo == taburcu_hastaNo && head -> next != NULL) {
            hasta *p = head->next;
            free(head);
            head = p;
            printf("%d No lu hasta taburcu edildi...\n",taburcu_hastaNo);
            sonuc = true;
        }

        else {
            hasta *p, *q;
            p = head;
            q=p;

            while (p->next != NULL) {
                if (p->hastaNo == taburcu_hastaNo) {
                    q->next = p->next;
                    free(p);
                    printf("%d No lu hasta taburcu edildi...\n",taburcu_hastaNo);
                    sonuc = true;
                    break;
                }
                q = p;
                p = p->next;
            }

            if (p->hastaNo == taburcu_hastaNo) {
                q->next = NULL;
                free(p);
                printf("%d No lu hasta taburcu edildi...\n",taburcu_hastaNo);
                sonuc = true;
            }
        }
        if (!sonuc) {
            printf("Hasta Bulunamadi...\n");
        }
    }
    return head;
}

hasta *hastalariGoruntule(hasta *head) {

    if (head == NULL) {
        printf("Hasta Yok...\n");
    }

    else {

        hasta *p;
        p = head;

        printf("\n---- Hasta Listesi ----\n");
        while (p != NULL) {
            printf("Hasta No: %d\n",p->hastaNo);
            printf("Hasta AdSoyad: %s\n",p->hasta_adSoyad);
            printf("Hasta TC: %s\n",p->tc);
            printf("Sikayet: %s\n",p->sikayet);
            printf("Oncelik: %d\n",p->oncelik);
            printf("Yas: %d\n",p->yas);
            printf("------------------------\n");
            p = p->next;
        }
    }
    return head;
}

hasta *oncelikSirasiGoruntule(hasta *head) {

    if (head == NULL) {
        printf("Hasta Yok...\n");
    }

    else {
        hasta *temp;

        printf("\n---- Hasta Oncelik Listesi ----\n");
        for (temp = head; temp != NULL; temp = temp->next) {
            if (temp -> oncelik == 1) {
                printf("Hasta No: %d\n",temp->hastaNo);
                printf("Hasta AdSoyad: %s\n",temp->hasta_adSoyad);
                printf("Hasta TC: %s\n",temp->tc);
                printf("Sikayet: %s\n",temp->sikayet);
                printf("Oncelik: %d\n",temp->oncelik);
                printf("Yas: %d\n",temp->yas);
                printf("------------------------\n");
            }
        }

        for (temp = head; temp != NULL; temp = temp->next) {
            if (temp -> oncelik == 2) {
                printf("Hasta No: %d\n",temp->hastaNo);
                printf("Hasta AdSoyad: %s\n",temp->hasta_adSoyad);
                printf("Hasta TC: %s\n",temp->tc);
                printf("Sikayet: %s\n",temp->sikayet);
                printf("Oncelik: %d\n",temp->oncelik);
                printf("Yas: %d\n",temp->yas);
                printf("------------------------\n");
            }
        }

        for (temp = head; temp != NULL; temp = temp->next) {
            if (temp -> oncelik == 3) {
                printf("Hasta No: %d\n",temp->hastaNo);
                printf("Hasta AdSoyad: %s\n",temp->hasta_adSoyad);
                printf("Hasta TC: %s\n",temp->tc);
                printf("Sikayet: %s\n",temp->sikayet);
                printf("Oncelik: %d\n",temp->oncelik);
                printf("Yas: %d\n",temp->yas);
                printf("------------------------\n");
            }
        }
    }
    return head;
}

gunluk *hastaReceteYaz(hasta *head, gunluk *head1) {

    if (head == NULL) {
        printf("Hasta Yok...\n");
    }

    else {
        gunluk *yeni_gunluk = (gunluk *)malloc(sizeof(gunluk));
        char ad_soyad[30];
        char ilac[30];
        int doz;
        printf("Hastanin adini girin: \n");
        fgets(ad_soyad,30,stdin);
        ad_soyad[strcspn(ad_soyad, "\n")] = 0;

        printf("Verilecek ilacin adi: \n");
        fgets(ilac,30,stdin);
        ilac[strcspn(ilac, "\n")] = 0;

        printf("Doz(mg): \n");
        scanf(" %d",&doz);
        getchar(); // scanf sonrası tamponu temizle

        char new_message[300];
        sprintf(new_message,"MSH|^~\\&|EMR|HOSPITAL|PHARMACY|202503011230||RDE^O11|741258|P|2.3\n"
                                  "PID|1||123456^^^HOSPITAL|987654321|%s|19850101|M\n"
                                  "RXO|12345^%s %dMG^RX|500|MG\n"
                                  "RXR|PO\n",ad_soyad,ilac,doz);



        strcpy(yeni_gunluk->message,new_message);
        yeni_gunluk->next = head1;
        head1 = yeni_gunluk;

        printf("------------------------\n");
        printf("Gunluk Guncellendi\n");
        printf("------------------------\n");
    }
    return head1;
}

gunluk *gunluguGor(gunluk *head1) {
    if (head1 == NULL) {
        printf("Gunluk bos, hasta ekleyin veya ilac yazin...\n");
    }

    else {
        gunluk *temp;
        temp = head1;

        printf("------------------------\n");
        while (temp != NULL) {
            printf("%s",temp -> message);
            printf("------------------------\n");

            temp = temp->next;
        }
    }

    return head1;
}

int main() {
    hasta *head = NULL;
    gunluk *head1 = NULL;


    int secim0 = 0;
    int hastaNo = 0;

    printf("----------------------------------------------------------\n");
    printf("             HASTANE PERSONEL TERMINALI\n");
    printf("----------------------------------------------------------\n");
    printf("Hasta ekle                --> '1' \n"
           "Hasta taburcu et          --> '2' \n"
           "Oncelik sirasi goruntule  --> '3' \n"
           "Hasta listesini goruntule --> '4' \n"
           "Gunlugu goruntule         --> '5' \n"
           "Ilac Yaz                  --> '6' \n"
           "Terminalden ayril         --> '7' \n");


    while (1) {
        printf("----------------------------------------------------------\n");
        printf("Islem sec: ");
        scanf("%d", &secim0);
        getchar(); // Clear buffer

        if (secim0 == 1) {
            head = yeniHastaKayit(head,hastaNo);
            head1 = gunlukEkle(head,head1);
            hastaNo++;
            a++;
        }
        else if (secim0 == 2) {
            head = hastaTaburcuEt(head);
        }
        else if (secim0 == 3) {
            head = oncelikSirasiGoruntule(head);
        }
        else if (secim0 == 4) {
            head = hastalariGoruntule(head);
        }
        else if(secim0 == 5) {
            head1 = gunluguGor(head1);
        }
        else if (secim0 == 6) {
            head1 = hastaReceteYaz(head,head1);
        }
        else if (secim0 == 7) {
            printf("Terminalden cikiliyor...\n");
            break;
        }
        else {
            printf("Gecersiz secim! Lutfen 1-7 arasinda bir deger girin.\n");
        }
    }
    return 0;
}