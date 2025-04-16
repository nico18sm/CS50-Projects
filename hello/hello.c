#include <stdio.h>
#include <cs50.h>

int main(void){
    string answer = get_string("Whats your name? ");
    int x = 10;
    int y = 5; 
        if(x > y){
            return "X is bigger than Y";
        }
        else{
            return "Y is bigger than X";
        }
    printf("Hello, %s\n", answer);
}