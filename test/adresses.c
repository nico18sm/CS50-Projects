#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main (void)
{
    int n = 0;
    int *p = &n;
    printf("%p\n", p);

    char *str = "hallo";
    printf("%s\n", str);
}
