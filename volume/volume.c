#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int copyHeader(FILE *input, FILE *output);
int manipulateVolume(FILE *input, FILE *output, float factor);

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        return 1;
    }

    //Übergebene Daten und Dateien
    char *start = argv[1];
    char *target = argv[2];
    float factor = atof(argv[3]);

    //Öffnen der Übergebenen Dateien + Error Handling
    FILE *input = fopen(start, "rb");
    if (input == NULL)
    {
        printf("Fehler beim Öffnen der Übermittelten Datei");
        return 2;
    }
    FILE *output = fopen(target, "wb");
    if(output == NULL){
        printf("Fehler beim Erstellen der Übersetzten Datei");
        return 5;
    }

    //Kopiert den Header der Übermittelten Datei an die Neue
    int result = copyHeader(input, output);
    if (result != 0)
    {
        printf("Fehler beim Kopieren des Headers");
        return 3;
    }
    //Verändert die Daten mit dem gewollten Multiplikator
    manipulateVolume(input, output, factor);
    fclose(input);
    fclose(output);
    return 0;
}


//Kopiert den Header in die neue Datei
int copyHeader(FILE *input, FILE *output)
{
    char header[44];
    size_t bytecopy = fread(header, 1, 44, input);
    if (bytecopy != 44)
    {
        fclose(input);
        return 3;
    }
    size_t bytetarget = fwrite(header, 1, 44, output);
    if (bytetarget != 44)
    {
        fclose(output);
        return 4;
    }
    return 0;
}

//Manipuliert die Daten mit dem gegebenen Faktor
int manipulateVolume(FILE *input, FILE *output, float factor)
{
    fseek(input, 44, SEEK_SET);
    short value;
    while (fread(&value, 2, 1, input) == 1)
    {
        value*= factor;

        fwrite(&value, 2, 1, output);
    }
    return 0;
}
