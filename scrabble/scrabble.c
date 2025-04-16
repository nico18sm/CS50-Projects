#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getSum(string s);
void getWinner(int sum1, int sum2);

int arr[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int sum1 = getSum(player1);
    int sum2 = getSum(player2);

    getWinner(sum1, sum2);
}

int getSum(string s) // Berechnet die Summe des Spielers pro Runde
{
    int sum = 0;
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (s[i] < 65 || s[i] > 122) //
        {
            sum += 0;
            continue;
        }
        if (s[i] > 90)
        {
            int asci = s[i] - 97;
            sum += arr[asci];
        }
        else
        {
            int asci = s[i] - 65;
            sum += arr[asci];
        }
    }
    return sum;
}

void getWinner(int sum1, int sum2) // Berechnet Sieger
{
    if (sum1 > sum2)
    {
        printf("Player 1 wins!\n");
    }
    else if (sum2 > sum1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
