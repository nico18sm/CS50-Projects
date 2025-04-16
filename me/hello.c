#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your Name?: "); // get username
    printf("hello, %s\n", name);                     // say hello to the user
}
