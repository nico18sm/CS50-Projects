#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int getAvgS(string input);
int getAvgL(string input);
int getWords(string input);

int main(void)
{
    string input = get_string("Text: ");
    int i = strlen(input);
    int letters = 0;
    int words = 0;
    int sentences = 0;

        for (int x = 0; x < i; x++)
    {
        // Counting letters
        char c = input[x];
        if (isalpha(c) != 0)
        {
            letters++;
        }

        // Counting words
        if (c == ' ')
        {
            words++;
        }

        // Counting Sentences
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }
    words = words + 1;

    float L = ((float)letters / (float)words) * 100;
    float s = ((float)sentences / (float)words) * 100;
    float subindex = 0.0588 * L - 0.296 * s - 15.8;
    int index = round(subindex);

        if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
/*

int getWords(string input)
{
    int words = 1;
    for(int i = 0; i < strlen(input); i++)
    {
        if(input[i] == ' ')
        {
            words += 1;
        }
    }
    return words;
}


int getAvgL(string input)
{
    int wörter = getWords(input);
    int chara = 0;
    for(int i = 0; i < strlen(input); i++)
    {
        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
        {
            chara++;
        }

    }
    return ((float)chara / (float)wörter) * 100;
}


int getAvgS(string input)
{
    int wörter = getWords(input);
    int sentence = 0;
    for(int i = 0; i < strlen(input); i++)
    {
        if (input[i] == 46 || input[i] == 63 || input[i] == 33)
        {
            sentence++;
        }
    }

   return ((float)sentence / (float)wörter) * 100;
}
*/

