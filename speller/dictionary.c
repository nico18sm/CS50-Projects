#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Größe der Hash-Tabelle (eine für jeden Buchstaben plus Apostroph z. B. für „it's“)
#define N 27

// Wortlänge aus dictionary.h
#define LENGTH 45

// Definition eines Knotens
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hash-Tabelle
node *table[N];

// Anzahl geladener Wörter
unsigned int word_count = 0;

// Hash-Funktion: Gibt Index 0–26 zurück
unsigned int hash(const char *word)
{
    char c = tolower(word[0]);
    if (c == '\'')
    {
        return 26;
    }
    return c - 'a';
}

// Lädt Wörter aus dem Wörterbuch in den Speicher
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        int index = hash(word);

        // Einfügen am Anfang der verketteten Liste
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    fclose(file);
    return true;
}

// Prüft, ob das Wort im Wörterbuch enthalten ist
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';

    int index = hash(temp);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, temp) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Gibt die Anzahl der Wörter im Wörterbuch zurück
unsigned int size(void)
{
    return word_count;
}

// Gibt den belegten Speicher frei
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
