#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    while (n <= 0 || n > 8)
    {
        n = get_int("Height?: "); // get number of height from user
    }
    for (int x = 1; x <= n; x++)
    { // schleife für die rows

        for (int i = 0; i < n - x; i++)
        {
            printf(" "); // regelt den abstand damit die pyramide abwärts läuft
        }
        for (int y = 0; y < x; y++)
        {
            printf("#");
        }
        printf("  "); // regelt die lücke in der mitte 
        for (int sec = 0; sec < x; sec++) // regelt den zweiten teil der pyramide
        {
            printf("#");
        }
        printf("\n");
    }
}
