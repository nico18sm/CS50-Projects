#include <stdio.h>
#include <cs50.h>

int recursion(int n);
int main(void){
    int n = get_int("Number: ");
    int target = recursion(n);
    printf("%d\n", target);
}

int recursion(int n){
    if(n == 1){
        return 0;
    }
    else if ((n % 2) == 0){
         return 1 + recursion(n/2);

    }
    else {
        return 1 + recursion(3*n + 1);
    }
}
