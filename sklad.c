#include <stdio.h>
#include <string.h>

#define MAX_PRODUKTU 10

// Struktura Produkt – reprezentuje jeden produkt ve skladu
typedef struct {
    char nazev[50];
    float cena;
    int kusy;
} Produkt;

// Funkce odstraní
void odstranNovyRadek(char *text) {
    text[strcspn(text, "\n")] = '\0';
}

// Vypíše všechny produkty ve skladu
void vypisProdukty(Produkt sklad[], int pocet) {
    // Pokud je sklad prázdný
    if (pocet == 0) {
        printf("Sklad je prazdny.\n");
        return;
    }

    printf("\nINDEX | NAZEV | CENA | KUSY\n");
    // Výpis všech produktů
    for (int i = 0; i < pocet; i++) {
        printf("%d | %s | %.2f | %d\n",
               i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
    }
}

// Vyhledá produkt podle přesného názvu
void vyhledatNazev(Produkt sklad[], int pocet) {
    char hledany[50];

    printf("Zadej cely nazev produktu: ");
    fgets(hledany, sizeof(hledany), stdin);
    odstranNovyRadek(hledany);

    // Projde všechny produkty a porovná názvy
    for (int i = 0; i < pocet; i++) {
        if (strcmp(sklad[i].nazev, hledany) == 0) {
            printf("Nalezen produkt (index %d): %s | %.2f | %d ks\n",
                   i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
            return;
        }
    }

    printf("Produkt nebyl nalezen.\n");  // Pokud se produkt nenašel
}

// Vyhledá produkty podle cenového rozmezí
void vyhledatCenu(Produkt sklad[], int pocet) {
    float min, max;

    printf("Cena OD: ");
    scanf("%f", &min);
    printf("Cena DO: ");
    scanf("%f", &max);
    getchar(); // vycisteni bufferu

    // Vypíše produkty, jejichž cena je v zadaném rozsahu
    for (int i = 0; i < pocet; i++) {
        if (sklad[i].cena >= min && sklad[i].cena <= max) {
            printf("%d | %s | %.2f | %d\n",
                   i, sklad[i].nazev, sklad[i].cena, sklad[i].kusy);
        }
    }
}

// Zobrazí detail jednoho produktu podle indexu
void detailProduktu(Produkt sklad[], int pocet) {
    int index;

    printf("Zadej index produktu: ");
    scanf("%d", &index);
    getchar();

    // Kontrola platnosti indexu
    if (index < 0 || index >= pocet) {
        printf("Neplatny index.\n");
        return;
    }

    // Výpis detailních informací
    printf("\nDETAIL PRODUKTU\n");
    printf("Index: %d\n", index);
    printf("Nazev: %s\n", sklad[index].nazev);
    printf("Cena: %.2f\n", sklad[index].cena);
    printf("Kusy: %d\n", sklad[index].kusy);
}

// Odstraní produkt ze skladu podle indexu
void odstranitProdukt(Produkt sklad[], int *pocet) {
    int index;

    printf("Zadej index produktu k odstraneni: ");
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= *pocet) {
        printf("Neplatny index.\n");
        return;
    }

    // Posunutí produktů doleva (přepsání odstraněného)
    for (int i = index; i < *pocet - 1; i++) {
        sklad[i] = sklad[i + 1];
    }

    (*pocet)--;
    printf("Produkt byl odstranen.\n");
}

// Upraví existující produkt
void upravitProdukt(Produkt sklad[], int pocet) {
    int index;

    printf("Zadej index produktu: ");
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= pocet) {
        printf("Neplatny index.\n");
        return;
    }

    // Zadání nových hodnot
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

    // Hlavní menu programu
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

        // Reakce na volbu uživatele
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
