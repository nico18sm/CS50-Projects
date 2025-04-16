#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool has_duplicates(string key);
string getEncrypt(string key, string input);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Bitte geben sie 26 Bustaben ein");
        return 1;
    }
    int length = strlen(argv[1]);
    if (length != 26) 
    {
        printf("Bitte geben sie 26 Bustaben ein");
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Der Schlüssel darf nur Buchstaben enthalten\n");
            return 1;
        }
    }
    if (has_duplicates(argv[1]))
    {
        printf("Der Schlüssel darf keine doppelten Buchstaben enthalten\n");
        return 1;
    }

    string key = malloc((length + 1) * sizeof(char));
    strcpy(key, argv[1]);
    for (int i = 0; i < length; i++)
    {
        key[i] = tolower(key[i]);
    }

    string input = get_string("plaintext: ");
    string target = getEncrypt(key, input);
    printf("ciphertext: %s\n", target);
    free(key);
    free(target);
    return 0;
}

string getEncrypt(string key, string input)
{
    int length = strlen(input);
    char *target = malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        int charSum = 0;

        if (isupper(input[i]))
        {
            charSum = input[i] - 'A';
            char zs = key[charSum];
            target[i] = toupper(zs);
        }
        else if (islower(input[i]))
        {
            charSum = input[i] - 'a';
            char zs = key[charSum];
            target[i] = tolower(zs);
        }
        else
        {
            target[i] = input[i];
        }
    }
    target[length] = '\0';
    return target;
}

bool has_duplicates(string key)
{
    // Array zur Verfolgung von Buchstaben
    bool seen[26] = {false};

    for (int i = 0; key[i] != '\0'; i++)
    {
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return true; // Duplikat gefunden
        }
        seen[index] = true;
    }
    return false; // Keine Duplikate
}
