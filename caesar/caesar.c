#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string getEncrypt(int key, string input);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Bitte geben sie eine Positive Zahl ein");
        return 1;
    }
    int length = strlen(argv[1]);
    string cla = argv[1];
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(cla[i]))
        {
            printf("Bitte geben sie eine Positive Zahl ein");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    string input = get_string("plaintext: ");
    string target = getEncrypt(key, input);
    printf("ciphertext: %s\n", target);
}

string getEncrypt(int key, string input)
{
    int length = strlen(input);
    char *target = malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        int charSum = 0;
        if (isupper(input[i]))
        {
            charSum = input[i] - 'A';
            int arrNum = (charSum + key) % 26;
            target[i] = 'A' + arrNum;
        }
        else if (islower(input[i]))
        {
            charSum = input[i] - 'a';
            int arrNum = (charSum + key) % 26;
            target[i] = 'a' + arrNum;
        }
        else
        {
            target[i] = input[i];
        }
    }
    target[length] = '\0';
    return target;
}
