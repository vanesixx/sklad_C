#include <stdio.h>
#include <string.h>

#define MAX_PRODUKTU 10

typedef struct {
    char nazev[50];
    float cena;
    int kusy;
} Produkt;

void odstranNovyRadek(char *text) {
    text[strcspn(text, "\n")] = '\0';
}

void vypisProdukty(Produkt sklad[], int pocet) {
    if (pocet == 0) {
        printf("Sklad je prazdny.\n");
        return;
    }

    printf("\nINDEX | NAZEV | CENA | KUSY\n");
    for (int i = 0; i < pocet; i++) {
        printf("%d | %s | %.2f | %d\n",
               i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
    }
}

void vyhledatNazev(Produkt sklad[], int pocet) {
    char hledany[50];

    printf("Zadej cely nazev produktu: ");
    fgets(hledany, sizeof(hledany), stdin);
    odstranNovyRadek(hledany);

    for (int i = 0; i < pocet; i++) {
        if (strcmp(sklad[i].nazev, hledany) == 0) {
            printf("Nalezen produkt (index %d): %s | %.2f | %d ks\n",
                   i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
            return;
        }
    }

    printf("Produkt nebyl nalezen.\n");
}

void vyhledatCenu(Produkt sklad[], int pocet) {
    float min, max;

    printf("Cena OD: ");
    scanf("%f", &min);
    printf("Cena DO: ");
    scanf("%f", &max);
    getchar(); // vycisteni bufferu

    for (int i = 0; i < pocet; i++) {
        if (sklad[i].cena >= min && sklad[i].cena <= max) {
            printf("%d | %s | %.2f | %d\n",
                   i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
        }
    }
}

void detailProduktu(Produkt sklad[], int pocet) {
    int index;

    printf("Zadej index produktu: ");
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= pocet) {
        printf("Neplatny index.\n");
        return;
    }

    printf("\nDETAIL PRODUKTU\n");
    printf("Index: %d\n", index);
    printf("Nazev: %s\n", sklad[index].nazev);
    printf("Cena: %.2f\n", sklad[index].cena);
    printf("Kusy: %d\n", sklad[index].kusy);
}

void odstranitProdukt(Produkt sklad[], int *pocet) {
    int index;

    printf("Zadej index produktu k odstraneni: ");
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= *pocet) {
        printf("Neplatny index.\n");
        return;
    }

    for (int i = index; i < *pocet - 1; i++) {
        sklad[i] = sklad[i + 1];
    }

    (*pocet)--;
    printf("Produkt byl odstranen.\n");
}

void upravitProdukt(Produkt sklad[], int pocet) {
    int index;

    printf("Zadej index produktu: ");
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= pocet) {
        printf("Neplatny index.\n");
        return;
    }

    printf("Novy nazev: ");
    fgets(sklad[index].nazev, sizeof(sklad[index].nazev), stdin);
    odstranNovyRadek(sklad[index].nazev);

    printf("Nova cena: ");
    scanf("%f", &sklad[index].cena);

    printf("Novy pocet kusu: ");
    scanf("%d", &sklad[index].kusy);
    getchar();

    printf("Produkt byl upraven.\n");
}

int main() {
    Produkt sklad[MAX_PRODUKTU] = {
        {"Notebook", 25000, 5},
        {"Mys", 500, 20},
        {"Klavesnice", 1200, 10}
    };

    int pocet = 3;
    char volba;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Vypis produktu\n");
        printf("2 - Vyhledat podle nazvu\n");
        printf("3 - Vyhledat podle ceny\n");
        printf("4 - Detail produktu\n");
        printf("5 - Odstranit produkt\n");
        printf("6 - Upravit produkt\n");
        printf("X - Konec\n");
        printf("Volba: ");

        scanf(" %c", &volba);
        getchar();

        switch (volba) {
            case '1': vypisProdukty(sklad, pocet); break;
            case '2': vyhledatNazev(sklad, pocet); break;
            case '3': vyhledatCenu(sklad, pocet); break;
            case '4': detailProduktu(sklad, pocet); break;
            case '5': odstranitProdukt(sklad, &pocet); break;
            case '6': upravitProdukt(sklad, pocet); break;
            case 'X':
            case 'x': printf("Program ukoncen.\n"); break;
            default: printf("Neplatna volba.\n");
        }

    } while (volba != 'X' && volba != 'x');

    return 0;
}
