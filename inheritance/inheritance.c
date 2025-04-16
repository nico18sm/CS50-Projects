#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struktur für eine Person
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

// Funktionsprototypen
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Zufallszahlengenerator initialisieren
    srand(time(0));

    // Eine Familie mit 3 Generationen erstellen
    person *p = create_family(3);

    // Familie ausgeben
    print_family(p, 0);

    // Speicher freigeben
    free_family(p);
}

// Funktion zum Erstellen einer Familie
person *create_family(int generations)
{
    // Speicher für eine neue Person allokieren
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        printf("Speicher konnte nicht zugewiesen werden.\n");
        return NULL;
    }

    // Falls es weitere Generationen gibt, Eltern erstellen
    if (generations > 1)
    {
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Erbe von den Eltern weitergeben
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }
    else
    {
        // Älteste Generation bekommt zufällige Allele
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    return p;
}

// Funktion zur Speicherfreigabe
void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    // Rekursiv die Eltern freigeben
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Person selbst freigeben
    free(p);
}

// Funktion zur Ausgabe der Familie
void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Einrückung entsprechend der Generation
    for (int i = 0; i < generation; i++)
    {
        printf("    ");
    }

    // Bluttyp ausgeben
    printf("Generation %d: blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Eltern ausgeben
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Funktion zur zufälligen Auswahl eines Allels
char random_allele(void)
{
    char alleles[] = {'A', 'B', 'O'};
    return alleles[rand() % 3];
}
