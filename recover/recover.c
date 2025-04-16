#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Checkt den Userinput
    if(argc != 1)
    {
        printf("Please Upload one File only\n");
        return 1;
    }
    int userInput = argv[1];
    //Erstellt Userdatei;
    FILE *file = fopen(userInput, "r");
    if(file == NULL)
    {
        printf("Error: File could not open");
        return 1;
    }

    int count = 0;
    char buffer(512);
    size_t bytes_read;

    while(count != 50)
    {
        while((bytes_read = fread(buffer, 1, 1, file)) > 0)
        {
            if()
        }
    }
}

